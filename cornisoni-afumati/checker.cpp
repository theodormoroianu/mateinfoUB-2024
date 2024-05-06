/**
 * Author:     Alexandru Tifui, Theodor Moroianu
*/

#include <bits/stdc++.h>
using namespace std;

// Global state of the interpreter.
int N;
vector <string> instructions;
vector <vector<string>> decoded_ops;
vector <int> reg(5, 0);
vector <int> perm;

int no_executed_instructions = 0;

const int NO_EXEC_INSTR_THRESHOLD = 10'000'000; // TODO choose this more carefully

bool DISPLAY_MOVES = false;

vector <string> DecodeInstruction(string instr) 
{
  vector <string> tokens;
  tokens.push_back("");
  for (auto i : instr) {
    if (i == ' ') {
      tokens.push_back("");
    }
    else {
      tokens.back().push_back(i);
    }
  }

  // removing the index of the instruction
  tokens.erase(tokens.begin());

  while (!tokens.empty() and tokens.back() == "")
    tokens.pop_back();
  return tokens;
}

bool IsVariableRegister(string s) 
{
  return s == "A" or s == "B" or s == "C" or s == "D" or s == "E";
}

bool IsConstantRegister(string s) 
{
  return s == "N" or s == "Z";
}

bool IsRegister(string s)
{
  return IsVariableRegister(s) or IsConstantRegister(s);
}

int GetRegisterValue(string s)
{
  assert(IsRegister(s));
  if (IsVariableRegister(s))
    return reg[s[0] - 'A'];
  if (s == "N")
    return N;
  if (s == "Z")
    return 0;
  assert(false);
}

bool FetchAndDecode(string instr, int expected_instruction_no) 
{
  int computed_instruction_no = 0;
  int pos = 0;
  int len = instr.size();
  while (pos < len and isdigit(instr[pos])) {
    computed_instruction_no = computed_instruction_no * 10 + instr[pos] - '0';
    pos++;
  }

  if (computed_instruction_no != expected_instruction_no) 
    return false;

  if (instr[pos] != '.')
    return false;
  pos++;

  if (instr[pos] != ' ')
    return false;
  pos++;

  vector <string> instruction = DecodeInstruction(instr);
  decoded_ops.push_back(instruction);

  if (instruction.size() < 1)
    return false;

  if (instruction[0] == "IF_LESS_GOTO" or instruction[0] == "IF_SAME_GOTO" or instruction[0] == "IF_DIFF_GOTO") {
    if (instruction.size() != 4)
      return false;

    if (!IsRegister(instruction[1]))
      return false;

    if (!IsRegister(instruction[2]))
      return false;

    if (stoi(instruction[3]) < 0 or stoi(instruction[3]) >= (int)instructions.size())
      return false;
  }
  else if (instruction[0] == "ASSIGN") {
    if (instruction.size() != 3)
      return false;

    if (!IsVariableRegister(instruction[1]))
      return false;

    if (!IsRegister(instruction[2]))
      return false;
  }
  else if (instruction[0] == "INC" or instruction[0] == "DEC" or instruction[0] == "PLOAD") {
    if (instruction.size() != 2)
      return false;

    if (!IsVariableRegister(instruction[1]))
      return false;
  }
  else if (instruction[0] == "SWAP" or instruction[0] == "PSWAP") {
    if (instruction.size() != 3)
      return false;

    if (!IsVariableRegister(instruction[1]))
      return false;

    if (!IsVariableRegister(instruction[2]))
      return false;
  }
  else if (instruction[0] == "END") {
    if (instruction.size() != 1)
      return false;
  }
  else
    return false;

  return true;
}

bool LoadAndValidateInstructions(ifstream& fout)
{
  string line;
  while (getline(fout, line)) {
    instructions.push_back(line);
  }

  int idx = 0;
  for (auto line : instructions) {
    if (!FetchAndDecode(line, idx)) {
      cerr << "Instruction " << line << " is invalid\n";
      return false;
    }
    idx++;
  }

  return true;
}

void ExecuteInstruction(vector <string> I, int &pc) 
{
  // do pc-- after the jump in case of GOTO instructions
  if (I[0] == "IF_LESS_GOTO") {
    int val1 = GetRegisterValue(I[1]);
    int val2 = GetRegisterValue(I[2]);

    if (val1 < val2) {
      pc = stoi(I[3]);
      pc--;
    }
  }
  else if (I[0] == "IF_DIFF_GOTO") {
    int val1 = GetRegisterValue(I[1]);
    int val2 = GetRegisterValue(I[2]);

    if (val1 != val2) {
      pc = stoi(I[3]);
      pc--;
    }
  }
  else if (I[0] == "IF_SAME_GOTO") {
    int val1 = GetRegisterValue(I[1]);
    int val2 = GetRegisterValue(I[2]);

    if (val1 == val2) {
      pc = stoi(I[3]);
      pc--;
    }
  }
  else if (I[0] == "ASSIGN") {
    int val2 = GetRegisterValue(I[2]);
    reg[I[1][0] - 'A'] = val2;
  }
  else if (I[0] == "INC") {
    reg[I[1][0] - 'A']++;
  }
  else if (I[1] == "DEC") {
    reg[I[1][0] - 'A']--;
  }
  else if (I[0] == "PLOAD") {
    int val = GetRegisterValue(I[1]);
    if (val < 0 or val >= N)
      throw "Runtime error";

    reg[I[1][0] - 'A'] = perm[val];
  }
  else if (I[0] == "SWAP") {
    int val1 = GetRegisterValue(I[1]);
    int val2 = GetRegisterValue(I[2]);

    reg[I[1][0] - 'A'] = val2;
    reg[I[2][0] - 'A'] = val1;
  }
  else if (I[0] == "PSWAP") {
    int val1 = GetRegisterValue(I[1]);
    if (val1 < 0 or val1 >= N)
      throw "Runtime error";

    int val2 = GetRegisterValue(I[2]);
    if (val2 < 0 or val2 >= N)
      throw "Runtime error";

    swap(perm[val1], perm[val2]);
  }
  else if (I[0] == "END") {
    pc = -2;
  }
  else
    throw "Runtime error";
}

void Execute()
{
  for (int pc = 0; pc < (int)decoded_ops.size(); pc++) {
    if (DISPLAY_MOVES) {
      cout << "Program counter   = " << pc << '\n';
      cout << "Permutation       = { ";
      for (int i = 0; i < N; i++)
        cout << perm[i] << ' ';
      cout << "}\n";
      cout << "Variable registers:";
      for (int i = 0; i < 5; i++)
        cout << "   * " << (char)('A' + i) << " = " << reg[i] << '\n';
      cout << "Instruction to run:\n     " <<  instructions[pc] << "\n\n";
    }

    ExecuteInstruction(decoded_ops[pc], pc);
    no_executed_instructions++;

    // cout << '\n';
    if (no_executed_instructions > NO_EXEC_INSTR_THRESHOLD)
      throw "Too many instructions\n";

    if (pc == -2) // END was called
      break;
  }
}

bool valid_output() 
{
  for (int i = 0; i < N; i++)
    if (perm[i] != i)
      return false;
  return true;
}

int main(int argc, char** argv)
{
  assert(argc == 4);

  string input_file(argv[1]);
  string output_file(argv[2]);
  string answer_file(argv[3]);
  
  ifstream fin(input_file);
  ifstream fout(output_file);
  ifstream fok(answer_file);

  // load_ok_data(fin, fok);
  fin >> N;
  perm.resize(N);

  try {
    if (!LoadAndValidateInstructions(fout)) {
      throw "Invalid input\n";
    }

    // try 10 random permutations of size N
    mt19937 rnd(time(0));
    for (int trial = 0; trial < 10; trial++) {
      iota(perm.begin(), perm.end(), 0);
      shuffle(perm.begin(), perm.end(), rnd);
      // reset all registers
      fill(reg.begin(), reg.end(), 0);
      no_executed_instructions = 0;
      auto original_permutation = perm;

      Execute();

      if (!valid_output()) {
        cout << "WA on trial " << trial << "\n";
        return 0;
        // cout << "Original permutation: " << '\n';
        // for (int i = 0; i < N; i++)
        //   cout << original_permutation[i] << ' ';
        // cout << '\n';
        // cout << "Final permutation: " << '\n';
        // for (int i = 0; i < N; i++)
        //   cout << perm[i] << ' ';
      }
    }
    cout << "OK\n";
  }
  catch(const char* e) {
    cout << "WA\n";
    cout << e << '\n';
  }


  return 0;
}
