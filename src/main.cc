#include <ios>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>

using std::cout;
using std::endl;
using std::cerr;
using std::cin;

static const int BENCHMARK_REPETATION = 500;

// A testing-purpose data struct.
struct TestDataType {
  int number;
  std::string st;
  double anohino_kana_shimi_sae;
  long long anohino_kuru_shimi_sae;
  bool sonosubeteo_aishiteta_anatato_tomoni;
};

// FW, copied from internet. (https://www.cnblogs.com/phemiku/p/11409055.html)
inline void fw(int x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)fw(x/10);
    putchar(x%10+'0');
}

// Improved FW
inline void fw_ex(int x){
    if(x<0){
        std::fputc('-', stdout);
        x=-x;
    }
    if(x>9)fw(x/10);
    std::fputc(x%10+'0', stdout);
}

// Generators

int g_rand_int() {
  return std::rand() % 1919810;
}

std::string g_rand_string() {
  std::string result;
  for (int i = 0; i < (rand() % 60); i++) {
    result.push_back(std::rand() % (0x7f - ' ') + ' ');
  }
  return result;
}

TestDataType g_rand_compound() {
  TestDataType result;
  result.number = g_rand_int();
  result.st = g_rand_string() + g_rand_string();
  result.anohino_kana_shimi_sae = double(g_rand_int()) / double(g_rand_int());
  result.anohino_kuru_shimi_sae = (long long)(g_rand_int()) * (long long)(g_rand_int()) * (long long)(g_rand_int()) * (long long)(g_rand_int());
  result.sonosubeteo_aishiteta_anatato_tomoni = (g_rand_int() % 2 == 0);
  return result;
}

// Preludes

void p_disable_sync_with_stdio() {
  std::ios_base::sync_with_stdio(false);
}

void p_disable_sync_with_stdio_and_untie() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
}

// Functions to test

void t_simple_output_using_cout() {
  cout << "Hello, World! ";
}

void t_simple_output_using_cout2() {
  cout << 114514;
}

void t_simple_output_using_printf() {
  printf("Hello, World! ");
}

void t_simple_output_using_printf2() {
  printf("%d", 114514);
}

void t_simple_output_using_quickwrite() {
  fw(114514);
}

void t_simple_output_using_quickwrite_ex() {
  fw_ex(114514);
}

void t_simple_output_using_puts() {
  std::puts("Hello, World! ");
}

void t_simple_output_using_cout_arged(std::string s) {
  cout << s;
}

void t_simple_output_using_cout2_arged(int i) {
  cout << i;
}

void t_simple_output_using_printf_arged(std::string s) {
  printf("%s", s.c_str());
}

void t_simple_output_using_printf2_arged(int i) {
  printf("%d", i);
}

void t_simple_output_using_quickwrite_arged(int i) {
  fw(i);
}

void t_simple_output_using_quickwrite_ex_arged(int i) {
  fw_ex(i);
}

void t_simple_output_using_puts_arged(std::string s) {
  std::puts(s.c_str());
}

void t_compound_output_using_cout(TestDataType obj) {
  cout << obj.number << " " << obj.st << " " << obj.anohino_kana_shimi_sae << " " << obj.anohino_kuru_shimi_sae << " ";
  if (obj.sonosubeteo_aishiteta_anatato_tomoni) {
    cout << "戻らない幸せがあることを・最後にあなたが教えてくれた";
  } else {
    cout << "言えずに隠してた昏い過去も・あなたがいなきゃ永遠に昏いまま";
  }
}

void t_compound_output_using_printf(TestDataType obj) {
  printf("%d %s %lf %lld ", obj.number, obj.st.c_str(), obj.anohino_kana_shimi_sae, obj.anohino_kuru_shimi_sae);
  if (obj.sonosubeteo_aishiteta_anatato_tomoni) {
    printf("戻らない幸せがあることを・最後にあなたが教えてくれた");
  } else {
    printf("言えずに隠してた昏い過去も・あなたがいなきゃ永遠に昏いまま");
  }
}

// Benchmarking function

void benchmark(void (* prelude)(void), void (* func)(void), const char * title = "") {

  using namespace std::chrono;

  unsigned long long t = 0;
  // Reset the state.
  auto ocint = cin.tie();
  auto ocoutt = cout.tie();

  for (int i = 0; i < BENCHMARK_REPETATION; i++) {
    if (prelude) {
      prelude();
    }
    time_point<high_resolution_clock> start, end;
    start = high_resolution_clock::now();
    func();
    end = high_resolution_clock::now();
    auto st = time_point_cast<nanoseconds>(start).time_since_epoch().count();
    auto ed = time_point_cast<nanoseconds>(end).time_since_epoch().count();
    t += ed - st;
    cout << "\nT SUM = " << t << endl;
  }
  cerr << "Benchmarking " << title << " took " << (t / BENCHMARK_REPETATION) << "ns. " << endl;

  // Recover the environment.
  std::ios_base::sync_with_stdio(true);
  cin.tie(ocint);
  cout.tie(ocoutt);

}

template <typename T>
void benchmark_arged(void (* prelude)(void), void (* func)(T), T (* generator)(void), const char * title = "") {

  using namespace std::chrono;

  unsigned long long t = 0;
  // Reset the state.
  auto ocint = cin.tie();
  auto ocoutt = cout.tie();

  for (int i = 0; i < BENCHMARK_REPETATION; i++) {
    if (prelude) {
      prelude();
    }
    time_point<high_resolution_clock> start, end;
    T value = generator();
    start = high_resolution_clock::now();
    func(value);
    end = high_resolution_clock::now();
    auto st = time_point_cast<nanoseconds>(start).time_since_epoch().count();
    auto ed = time_point_cast<nanoseconds>(end).time_since_epoch().count();
    t += ed - st;
    cout << "\nT SUM = " << t << endl;
  }
  cerr << "Benchmarking " << title << " took " << (t / BENCHMARK_REPETATION) << "ns. " << endl;

  // Recover the environment.
  std::ios_base::sync_with_stdio(true);
  cin.tie(ocint);
  cout.tie(ocoutt);

}

int main(void) {

  std::srand(std::time(NULL));

  cerr << "All tests are repeated " << BENCHMARK_REPETATION << " times. " << endl << endl;

  cout << "Test out goes ";
  printf("here. \n");

  // Testing simple outputs.
  cerr << "==============TEST FOR SIMPLE OUTPUTS==============" << endl;
  benchmark(nullptr, t_simple_output_using_cout, "Output a single string using cout");
  benchmark(nullptr, t_simple_output_using_cout2, "Output a single number using cout");
  benchmark(nullptr, t_simple_output_using_printf, "Output a single string using printf");
  benchmark(nullptr, t_simple_output_using_printf2, "Output a single number using printf");
  benchmark(nullptr, t_simple_output_using_quickwrite, "Output a single number using quick writing");
  benchmark(nullptr, t_simple_output_using_quickwrite_ex, "Output a single number using quick writing but use fXX-functions instead of putchar");
  benchmark(p_disable_sync_with_stdio, t_simple_output_using_cout, "Output a single string using cout with sync_with_stdio off");
  benchmark(p_disable_sync_with_stdio, t_simple_output_using_cout2, "Output a single number using cout with sync_with_stdio off");
  benchmark(p_disable_sync_with_stdio_and_untie, t_simple_output_using_cout, "Output a single string using cout with sync_with_stdio off and tie(0)s");
  benchmark(p_disable_sync_with_stdio_and_untie, t_simple_output_using_cout2, "Output a single number using cout with sync_with_stdio off and tie(0)s");
  benchmark(nullptr, t_simple_output_using_puts, "Output a single string using puts() ");
  cerr << "===================================================" << endl << endl;

  // Testing simple outputs using random data.
  cerr << "==========TEST FOR SIMPLE OUTPUTS (ARGED)==========" << endl;
  benchmark_arged(nullptr, t_simple_output_using_cout_arged, g_rand_string, "Output a single string using cout");
  benchmark_arged(nullptr, t_simple_output_using_cout2_arged, g_rand_int, "Output a single number using cout");
  benchmark_arged(nullptr, t_simple_output_using_printf_arged, g_rand_string, "Output a single string using printf");
  benchmark_arged(nullptr, t_simple_output_using_printf2_arged, g_rand_int, "Output a single number using printf");
  benchmark_arged(nullptr, t_simple_output_using_quickwrite_arged, g_rand_int, "Output a single number using quick writing");
  benchmark_arged(nullptr, t_simple_output_using_quickwrite_ex_arged, g_rand_int, "Output a single number using quick writing but use fXX-functions instead of putchar");
  benchmark_arged(p_disable_sync_with_stdio, t_simple_output_using_cout_arged,g_rand_string, "Output a single string using cout with sync_with_stdio off");
  benchmark_arged(p_disable_sync_with_stdio, t_simple_output_using_cout2_arged, g_rand_int, "Output a single number using cout with sync_with_stdio off");
  benchmark_arged(p_disable_sync_with_stdio_and_untie, t_simple_output_using_cout_arged, g_rand_string, "Output a single string using cout with sync_with_stdio off and tie(0)s");
  benchmark_arged(p_disable_sync_with_stdio_and_untie, t_simple_output_using_cout2_arged, g_rand_int, "Output a single number using cout with sync_with_stdio off and tie(0)s");
  benchmark_arged(nullptr, t_simple_output_using_puts_arged, g_rand_string, "Output a single string using puts() ");
  cerr << "===================================================" << endl << endl;

  // Testing compound outputs.
  cerr << "=============TEST FOR COMPOUND OUTPUTS=============" << endl;
  benchmark_arged(nullptr, t_compound_output_using_cout, g_rand_compound, "Output a compound data structure using cout");
  benchmark_arged(nullptr, t_compound_output_using_printf, g_rand_compound, "Output a compound data structure using printf");
  benchmark_arged(p_disable_sync_with_stdio, t_compound_output_using_cout, g_rand_compound, "Output a compound data structure using cout with sync_with_stdio off");
  cerr << "===================================================" << endl << endl;
}
