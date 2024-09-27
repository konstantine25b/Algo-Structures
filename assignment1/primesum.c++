// ვთქვათ, N მთელი დადებითი რიცხვია. აღვნიშნოთ SUM(N)-ით იმ ვარიანტების რაოდენობა, რომლითაც N შეიძლება წარმოდგენილი იყოს ორი ან მეტი მარტივი რიცხვის ჯამით. მაგალითად SUM(9)=4, რადგან 9=2+2+2+3=2+2+5=2+7=3+3+3. ვთქვათ, P იყოს უმცირესი მარტივი, რომელიც N-ზე მეტია. დაწერეთ პროგრამა, რომელიც იპოვის SUM(N)-ს P-ზე გაყოფის ნაშთს.

// Input
// შესატანი მონაცემები: ერთი მთელი რიცხვი - N (2<N<50000).

// Output
// გამოსატანი მონაცემები: ერთი მთელი რიცხვი - SUM(N)-ის P-ზე გაყოფის ნაშთი.

#include <iostream>
#include <vector>
#include <algorithm> 
#include <set>
using namespace std;

void findPrimesUpTo(int maxLimit, vector<int> &primeNumbers) {
    vector<bool> primeFlags(maxLimit + 1, true);
    primeFlags[0] = primeFlags[1] = false;
    for (int num = 2; num * num <= maxLimit; ++num) {
        if (primeFlags[num]) {
            for (int multiple = num * num; multiple <= maxLimit; multiple += num) {
                primeFlags[multiple] = false;
            }
        }
    }

    for (int k = 2; k <= maxLimit; ++k) {
        if (primeFlags[k]) {
            primeNumbers.push_back(k);
        }
    }
}

int main() {
  int n;
  cin>>n;

  int N = 50005;
  vector<int> primes;
  findPrimesUpTo(2*n, primes);
  int mod;
  set<int> primeSet;

  for(int i = 0 ;i<primes.size(); i++){
    primeSet.insert(primes[i]);
    if(primes[i]>n){
        mod= primes[i];
        break;
    }
  }
  
  vector<long long> dp(n + 1, 0);
    dp[0] = 1; 
    for (int i =0 ; i< primes.size() ; i++) {
        if(primes[i]==n) continue;
        for (int j = primes[i]; j <= n; j++) {
            
            dp[j] = (dp[j] + dp[j - primes[i]])%mod;
        }
    }
    
    cout << (dp[n] % mod) << endl;
  
  return 0;  
}