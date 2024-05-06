/**
 * Author:     Alexandru Tifui
*/

#include <bits/stdc++.h>

using namespace std;

vector <string> instructions;
vector <vector<string>> decoded_ops;
vector <int> reg(5, 0);
int N;
vector <int> perm;
// int benchmark;
int no_executed_instructions = 0;

const int NO_EXEC_INSTR_THRESHOLD = 50000; // TODO choose this more carefully

void load_ok_data(ifstream& fin, ifstream& fok)
{
  assert(fin >> N);
  perm.resize(N + 1);
  for (int i = 1; i <= N; i++) {
    assert(fok >> perm[i]);
    assert(0 < perm[i] and perm[i] <= N);
  }
  // assert(fok >> benchmark);
}

vector <string> split_instr(string instr, int pos) 
{
  vector <string> ans;
  ans.push_back("");
  for (int i = pos; i < (int)instr.size(); i++) {
    if (instr[i] == ' ') {
      ans.push_back("");
    }
    else {
      ans.back().push_back(instr[i]);
    }
  }

  while (!ans.empty() and ans.back() == "")
    ans.pop_back();
  return ans;
}

bool is_var_reg(string s) 
{
  return s == "A" or s == "B" or s == "C" or s == "D" or s == "E";
}

bool is_const_reg(string s) 
{
  return s == "N" or s == "Z";
}

bool is_reg(string s)
{
  return is_var_reg(s) or is_const_reg(s);
}

int get_reg_val(string s)
{
  assert(is_reg(s));
  if (is_var_reg(s))
    return reg[s[0] - 'A'];
  if (s == "N")
    return N;
  if (s == "Z")
    return 0;
  assert(false);
}

bool valid(string instr, int expected_no) 
{
  int ans = 0;
  int pos = 0;
  int len = instr.size();
  while (pos < len and isdigit(instr[pos])) {
    ans = ans * 10 + instr[pos] - '0';
    pos++;
  }

  if (ans != expected_no) 
    return false;

  if (instr[pos] != '.')
    return false;
  pos++;

  if (instr[pos] != ' ')
    return false;
  pos++;

  vector <string> I = split_instr(instr, pos);
  decoded_ops.push_back(I);
  if (I.size() < 2)
    return false;

  if (I[0] == "IF_LESS_GOTO" or I[0] == "IF_DIFF_THEN_GOTO") {
    if (I.size() != 4)
      return false;

    if (!is_reg(I[1]))
      return false;

    if (!is_reg(I[2]))
      return false;

    if (stoi(I[3]) < 0 or stoi(I[3]) >= (int)instructions.size())
      return false;
  }
  else if (I[0] == "ASSIGN") {
    if (I.size() != 3)
      return false;

    if (!is_var_reg(I[1]))
      return false;

    if (!is_reg(I[2]))
      return false;
  }
  else if (I[0] == "INC" or I[0] == "DEC" or I[0] == "PLOAD") {
    if (I.size() != 2)
      return false;

    if (!is_var_reg(I[1]))
      return false;

    // if (I[0] == "PLOAD") {
    //   int val = get_reg_val(I[1]);
    //   if (val < 1 or val > N)
    //     return false;
    // }
  }
  else if (I[0] == "SWAP" or I[0] == "PSWAP") {
    if (I.size() != 3)
      return false;

    if (!is_var_reg(I[1]))
      return false;

    if (!is_var_reg(I[2]))
      return false;

    // if (I[0] == "PSWAP") {
    //   int val1 = get_reg_val(I[1]);
    //   if (val1 < 1 or val1 > N)
    //     return false;

    //   int val2 = get_reg_val(I[2]);
    //   if (val2 < 2 or val2 > N)
    //     return false;
    // }
  }
  else
    return false;

  return true;
}

bool parse_instructions(ifstream& fout)
{
  string line;
  while (getline(fout, line)) {
    instructions.push_back(line);
  }

  int idx = 0;
  for (auto line : instructions) {
    if (!valid(line, idx))
      return false;
    idx++;
  }

  return true;
}

void execute_instruction(vector <string> I, int &pc) 
{
  // do pc-- after the jump in case of GOTO instructions
  if (I[0] == "IF_LESS_GOTO") {
    int val1 = get_reg_val(I[1]);
    int val2 = get_reg_val(I[2]);

    if (val1 < val2) {
      pc = stoi(I[3]);
      pc--;
    }
  }
  else if (I[0] == "IF_DIFF_THEN_GOTO") {
    int val1 = get_reg_val(I[1]);
    int val2 = get_reg_val(I[2]);

    if (val1 != val2) {
      pc = stoi(I[3]);
      pc--;
    }
  }
  else if (I[0] == "ASSIGN") {
    int val2 = get_reg_val(I[2]);
    reg[I[1][0] - 'A'] = val2;
  }
  else if (I[0] == "INC") {
    reg[I[1][0] - 'A']++;
  }
  else if (I[1] == "DEC") {
    reg[I[1][0] - 'A']--;
  }
  else if (I[0] == "PLOAD") {
    int val = get_reg_val(I[1]);
    if (val < 1 or val > N)
      throw "Runtime error";

    reg[I[1][0] - 'A'] = perm[val];
  }
  else if (I[0] == "SWAP") {
    int val1 = get_reg_val(I[1]);
    int val2 = get_reg_val(I[2]);

    reg[I[1][0] - 'A'] = val2;
    reg[I[2][0] - 'A'] = val1;
  }
  if (I[0] == "PSWAP") {
    int val1 = get_reg_val(I[1]);
    if (val1 < 1 or val1 > N)
      throw "Runtime error";

    int val2 = get_reg_val(I[2]);
    if (val2 < 2 or val2 > N)
      throw "Runtime error";

    swap(perm[val1], perm[val2]);
  }
  else
    throw "Runtime error";
}

void execute()
{
  for (int pc = 0; pc < (int)decoded_ops.size(); pc++) {
    execute_instruction(decoded_ops[pc], pc);
    no_executed_instructions++;

    if (no_executed_instructions > NO_EXEC_INSTR_THRESHOLD)
      throw "Too many instructions\n";
  }
}

bool valid_output() 
{
  for (int i = 1; i <= N; i++)
    if (perm[i] != i)
      return false;
  return true;
}

int main(int argc, char** argv)
{
  assert(argc == 3);

  string input_file(argv[1]);
  string output_file(argv[1]);
  string answer_file(argv[1]);
  
  ifstream fin(input_file);
  ifstream fout(output_file);
  ifstream fok(answer_file);

  load_ok_data(fin, fok);

  try {
    if (!parse_instructions(fout)) {
      throw "Invalid input\n";
    }

    execute();

    if (valid_output())
      cout << "OK\n";
    else
      cout << "WA\n";
  }
  catch(...) {
    cout << "WA\n";
  }

  return 0;
}