/**
 * Authors:     Alexandru Tifui, Theodor Moroianu
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * ------------------------------ VALIDATOR PARAMETERS
 * ------------------------------ Modify the values of the following constants
 * to configure the validator.
 */
// Set this to false for less verbose debugging output
bool DISPLAY_MOVES = true;
// Set this to false to see the moves when N becomes large
bool HIDE_MOVES_LARGE_N = true;
const int HIDE_MOVES_THRESHOLD = 50;
// Modify this variable for testing the program on a larger number of
// permutations
const int NO_TRIALS = 10;

// Global state of the interpreter
int N;
vector<string> instructions;
vector<vector<string>> decoded_ops;
vector<int> reg(5, 0);
vector<int> perm, original_permutation;

int no_executed_instructions = 0;

const int NO_EXEC_INSTR_THRESHOLD = 5'000'000;

vector<string> DecodeInstruction(string instr) {
  vector<string> tokens;
  tokens.push_back("");
  for (auto i : instr) {
    if (i == ' ') {
      tokens.push_back("");
    } else {
      tokens.back().push_back(i);
    }
  }

  // removing the index of the instruction
  tokens.erase(tokens.begin());

  while (!tokens.empty() and tokens.back() == "")
    tokens.pop_back();
  return tokens;
}

bool IsVariableRegister(string s) {
  return s == "A" or s == "B" or s == "C" or s == "D" or s == "E";
}

bool IsConstantRegister(string s) { return s == "N" or s == "Z"; }

bool IsRegister(string s) {
  return IsVariableRegister(s) or IsConstantRegister(s);
}

int GetRegisterValue(string s) {
  assert(IsRegister(s));
  if (IsVariableRegister(s))
    return reg[s[0] - 'A'];
  if (s == "N")
    return N;
  if (s == "Z")
    return 0;
  assert(false);
}

bool FetchAndDecode(string instr, int expected_instruction_idx) {
  int instruction_index = 0;
  int pos = 0;
  int len = instr.size();
  while (pos < len and isdigit(instr[pos])) {
    instruction_index = instruction_index * 10 + instr[pos] - '0';
    pos++;
  }

  if (instruction_index != expected_instruction_idx) {
    cout << "[!] Found " << instruction_index
         << " as the instruction index. Expected " << expected_instruction_idx
         << '\n';
    return false;
  }

  if (instr[pos] != '.') {
    cout << "[!] Expected `.` right after the instruction index\n";
    return false;
  }
  pos++;

  if (instr[pos] != ' ') {
    cout << "[!] Expected ` ` between the instruction index and the first "
            "instruction token\n";
    return false;
  }
  pos++;

  vector<string> instruction = DecodeInstruction(instr);
  decoded_ops.push_back(instruction);

  if (instruction.size() < 1) {
    cout << "[!] No instruction is specified\n";
    return false;
  }

  if (instruction[0] == "IF_LESS_GOTO" or instruction[0] == "IF_SAME_GOTO" or
      instruction[0] == "IF_DIFF_GOTO") {
    if (instruction.size() != 4) {
      cout << "[!] Invalid instruction arity\n";
      return false;
    }

    if (!IsRegister(instruction[1])) {
      cout << "[!] " << instruction[1] << " is not a valid variable\n";
      return false;
    }

    if (!IsRegister(instruction[2])) {
      cout << "[!] " << instruction[2] << " is not a valid variable\n";
      return false;
    }

    if (stoi(instruction[3]) < 0 or
        stoi(instruction[3]) >= (int)instructions.size()) {
      cout << "[!] " << stoi(instruction[3])
           << " is not a valid instruction index\n";
      return false;
    }
  } else if (instruction[0] == "ASSIGN") {
    if (instruction.size() != 3) {
      cout << "[!] Invalid instruction arity\n";
      return false;
    }

    if (!IsVariableRegister(instruction[1])) {
      cout << "[!] " << instruction[1]
           << " is not a valid non-constant variable\n";
      return false;
    }

    if (!IsRegister(instruction[2])) {
      cout << "[!] " << instruction[2] << " is not a valid variable\n";
      return false;
    }
  } else if (instruction[0] == "INC" or instruction[0] == "DEC" or
             instruction[0] == "PLOAD") {
    if (instruction.size() != 2) {
      cout << "[!] Invalid instruction arity\n";
      return false;
    }

    if (!IsVariableRegister(instruction[1])) {
      cout << "[!] " << instruction[1]
           << " is not a valid non-constant variable\n";
      return false;
    }
  } else if (instruction[0] == "SWAP" or instruction[0] == "PSWAP") {
    if (instruction.size() != 3) {
      cout << "[!] Invalid instruction arity\n";
      return false;
    }

    if (!IsVariableRegister(instruction[1])) {
      cout << "[!] " << instruction[1]
           << " is not a valid non-constant variable\n";
      return false;
    }

    if (!IsVariableRegister(instruction[2])) {
      cout << "[!] " << instruction[2]
           << " is not a valid non-constant variable\n";
      return false;
    }
  } else if (instruction[0] == "END") {
    if (instruction.size() != 1) {
      cout << "[!] Invalid instruction arity\n";
      return false;
    }
  } else {
    cout << "[!] Instruction " << instruction[0] << " does not exist\n";
    return false;
  }

  return true;
}

bool LoadAndValidateInstructions() {
  cout << "Enter the number of instructions your program has:\n> ";
  int no_lines;
  cin >> no_lines;
  cout << "Enter " << no_lines
       << " lines containing the program (indexed from 0 to " << no_lines - 1
       << "):\n";
  string line;
  cin.ignore();
  for (int i = 0; i < no_lines; i++) {
    line = "";
    while (line == "")
      getline(cin, line);
    instructions.push_back(line);
  }

  cout << "\n";
  cout << "[TRYING TO DECODE THE PROVIDED PROGRAM]\n";
  // cout << "The input has " << instructions.size() << " lines\n";

  int idx = 0;
  for (auto instr : instructions) {
    if (!FetchAndDecode(instr, idx)) {
      cout << "[!] Instruction " << instr << " is invalid\n";
      return false;
    } else {
      cout << "[+] " << instr << "\n";
    }
    idx++;
  }

  cout << "[PROGRAM DECODED SUCCESSFULLY]\n\n\n";
  return true;
}

void ExecuteInstruction(vector<string> I, int &pc) {
  // do pc-- after the jump in case of GOTO instructions
  if (I[0] == "IF_LESS_GOTO") {
    int val1 = GetRegisterValue(I[1]);
    int val2 = GetRegisterValue(I[2]);

    if (val1 < val2) {
      pc = stoi(I[3]);
      pc--;
    }
  } else if (I[0] == "IF_DIFF_GOTO") {
    int val1 = GetRegisterValue(I[1]);
    int val2 = GetRegisterValue(I[2]);

    if (val1 != val2) {
      pc = stoi(I[3]);
      pc--;
    }
  } else if (I[0] == "IF_SAME_GOTO") {
    int val1 = GetRegisterValue(I[1]);
    int val2 = GetRegisterValue(I[2]);

    if (val1 == val2) {
      pc = stoi(I[3]);
      pc--;
    }
  } else if (I[0] == "ASSIGN") {
    int val2 = GetRegisterValue(I[2]);
    reg[I[1][0] - 'A'] = val2;
  } else if (I[0] == "INC") {
    reg[I[1][0] - 'A']++;
  } else if (I[0] == "DEC") {
    reg[I[1][0] - 'A']--;
  } else if (I[0] == "PLOAD") {
    int val = GetRegisterValue(I[1]);
    if (val < 0 or val >= N) {
      cout << "[!] The value of variable " << I[1] << " is " << val
           << " which is invalid\n";
      throw "Runtime error";
    }

    reg[I[1][0] - 'A'] = perm[val];
  } else if (I[0] == "SWAP") {
    int val1 = GetRegisterValue(I[1]);
    int val2 = GetRegisterValue(I[2]);

    reg[I[1][0] - 'A'] = val2;
    reg[I[2][0] - 'A'] = val1;
  } else if (I[0] == "PSWAP") {
    int val1 = GetRegisterValue(I[1]);
    if (val1 < 0 or val1 >= N) {
      cout << "[!] The value of variable " << I[1] << " is " << val1
           << " which is invalid\n";
      throw "Runtime error";
    }

    int val2 = GetRegisterValue(I[2]);
    if (val2 < 0 or val2 >= N) {
      cout << "[!] The value of variable " << I[2] << " is " << val2
           << " which is invalid\n";
      throw "Runtime error";
    }

    swap(perm[val1], perm[val2]);
  } else if (I[0] == "END") {
    pc = -2;
  } else
    throw "Runtime error";
}

void Execute(int trial) {
  for (int pc = 0; pc < (int)decoded_ops.size(); pc++) {
    if (DISPLAY_MOVES) {
      cout << "\nvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n";
      cout << "Nr instructions executed: " << no_executed_instructions << "\n";
      cout << "Next instruction to run:  " << instructions[pc] << "\n";
      cout << "Permutation:              { ";
      for (int i = 0; i < N; i++)
        cout << perm[i] << ' ';
      cout << "}\n";
      cout << "Variables:                * A = " << reg[0] << '\n';
      for (int i = 1; i < 5; i++)
        cout << "                          * " << (char)('A' + i) << " = "
             << reg[i] << '\n';
      cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n\n";
    }

    ExecuteInstruction(decoded_ops[pc], pc);
    no_executed_instructions++;

    if (no_executed_instructions > NO_EXEC_INSTR_THRESHOLD)
      throw "Too many instructions\n";

    if (pc == -2) // END was called
      break;
  }

  cout << "Total number of executed instructions: " << no_executed_instructions
       << '\n';
  cout << "Original permutation:                  { ";
  for (int i = 0; i < N; i++)
    cout << original_permutation[i] << ' ';
  cout << "}\n";
  cout << "Final permutation:                     { ";
  for (int i = 0; i < N; i++)
    cout << perm[i] << ' ';
  cout << "}\n";
  cout << "[END OF EXECUTION " << trial + 1 << "/" << NO_TRIALS << "]\n\n\n";
}

bool ValidOutput() {
  for (int i = 0; i < N; i++)
    if (perm[i] != i) {
      return false;
    }

  return true;
}

mt19937 rnd(time(0));

void GenerateRandomPerm(int trial) {
  iota(perm.begin(), perm.end(), 0);
  shuffle(perm.begin(), perm.end(), rnd);

  // Reset the state of the interpreter
  fill(reg.begin(), reg.end(), 0);
  no_executed_instructions = 0;
  original_permutation = perm;

  cout << "[START OF EXECUTION " << trial + 1 << "/" << NO_TRIALS << "]\n";
  cout << "Using input permutation: { ";
  for (int i = 0; i < N; i++)
    cout << perm[i] << ' ';
  cout << "}\n";
}

int main() {
  cout << "========================= WARNING!!! =========================\n";
  cout << "You can customize the validator by changing the "
          "apropriate\nconstants defined "
          "at the beginning of the file.\n";
  cout << "==============================================================\n";

  try {
    cout << "\nEnter the value for N (the permutation length):\n> ";
    cin >> N;

    if (N < 0) {
      cout << "The value for N should not be negative\n";
      throw "Invalid input\n";
    }
    if (N > 1e5) {
      cout << "The value for N should not be larger than 100000\n";
      throw "Invalid input\n";
    }
    if (N > HIDE_MOVES_THRESHOLD and HIDE_MOVES_LARGE_N) {
      cout << "Hiding the moves, as N is too large (this would slow down stdout)\n";
      cout << "If you want to see the moves, set HIDE_MOVES_LARGE_N to false at the beginning of the file\n";
      DISPLAY_MOVES = false;
    }
    perm.resize(N);

    if (!LoadAndValidateInstructions()) {
      throw "Invalid input\n";
    }

    // try NO_TRIALS random permutations of size N
    cout << "[TESTING THE PROGRAM ON " << NO_TRIALS
         << " RANDOM PERMUTATIONS]\n\n\n";
    for (int trial = 0; trial < NO_TRIALS; trial++) {
      GenerateRandomPerm(trial);
      Execute(trial);
      if (!ValidOutput()) {
        cout << "WA on trial " << trial << "\n";
        return 0;
      }
    }
    cout << "======== [+] OK ON ALL TESTS [+] ======== \n";
  } catch (const char *e) {
    cout << e << '\n';
  }

  return 0;
}
