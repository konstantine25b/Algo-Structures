// A. ორი მართკუთხედი
// time limit per test1 second
// memory limit per test256 megabytes
// ორგანზომილებიან სიბრტყეზე მოცემულია N განსხვავებული კოორდინატების მქონე წერტილი (3≤N≤50000). მოაქციეთ ისინი ორი მართკუთხედის შიგნით ისე, რომ ამ მართკუთხედების ფართობების ჯამი იყოს მინიმალური. მართკუთხედების გვერდები x და y საკოორდინატო ღერძების პარალელური უნდა იყოს. მართკუთხედები არ უნდა ჰკვეთდნენ და არც უნდა ეხებოდნენ ერთმანეთს. დასაშვებია, რომ წერტილები მდებარეობდნენ მართკუთხედის გვერდებზე. შესაძლებელია, რომ ერთ-ერთი მართკუთხედის ფართობი იყოს 0-ის ტოლი (ნულოვანი სიგანე და/ან ნულოვანი სიმაღლე).

// .

// Input
// შესატანი მონაცემები: პირველი სტრიქონი შეიცავს ერთ მთელ რიცხვს N, რომელიც აღნიშნავს წერტილების რაოდენობას. მომდევნო N სტრიქონიდან თითოეული შეიცავს ორ მთელ რიცხვს - შესაბამის წერტილის კოორდინატებს. კოორდინატები წარმოადგენენ დადებით მთელ რიცხვებს ერთიდან მილიარდამდე დიაპაზონში.

// Output
// გამოსატანი მონაცემები: ერთადერთ სტრიქონში ერთი მთელი რიცხვი - სხვაობა ორ სიდიდეს შორის: ფართობს, რომელიც საჭირო იქნებოდა ყველა წერტილის ერთი მართკუთხედით დაფარვისას, უნდა გამოვაკლოთ ორი მართკუთხედის მინიმალური ჯამური ფართობი, რომელიც ასევე დაფარავს ყველა წერტილს.

#include <iostream>
#include <vector>
#include <algorithm> 
#include <set>
// #include <bits/stdc++.h>
using namespace std;


int main() {
  int n;
  cin>>n;
  vector<int> xElems(n);
  vector<int> yElems(n);
  vector<int> xElems1(n);
  vector<int> yElems1(n);
  
  for (int i = 0; i<n;i++ ){
    cin>>xElems[i];
    cin>>yElems[i];
    xElems1[i]=xElems[i];
    yElems1[i]=yElems[i];
  }
  sort(xElems.begin(),xElems.end());
  sort(yElems.begin(),yElems.end());
  int maxX = xElems[n-1]- xElems[0];
  int maxY = yElems[n-1]- yElems[0];
  long long maxArea = (long long) maxY * maxX;
  long long s3= maxArea;

  for(int i = 0 ; i< n ; i++){
    int curX= xElems1[i];
    for(int j = 0 ; j< n ; j++){
        int curY= yElems1[j];
        int lowestX=xElems[n-1];
        int lowestY=yElems[n-1];
       
        for(int k = 0;k < n;k++){
            if(xElems1[k]<=curX&& yElems1[k]>curY){
                lowestX = min(lowestX, xElems1[k]);
            }
            else if(xElems1[k]>curX){
                lowestX = min(lowestX, xElems1[k]);
            }
        }
        for(int k = 0;k < n;k++){
            if(yElems1[k]<=curY&& xElems1[k]>curX){
                lowestY = min(lowestY, yElems1[k]);
            }
            else if(yElems1[k]>curY){
                lowestY = min(lowestY, yElems1[k]);
            }
            
        }
        long long s1 =(long long) (yElems[n-1]-lowestY) * (xElems[n-1]-lowestX);
        long long s2 = (long long)(curX - xElems[0])* (curY - yElems[0]);
        // cout << "Current s1: " << s1 << " Coordinates: X: " << lowestX << ", Y: " << lowestY << endl;
        // cout << "Current s2: " << s2 << " Coordinates: X: " << curX << ", Y: " << curY << endl;
        if(s3>s1+s2){
             s3 = s1+s2;
        }

    }
  }
  cout<<maxArea-s3<<endl;




  return 0;
  
  
}

#include <iostream>
#include <vector>

using namespace std;

void fillVector(int N, vector<int>& primes){
    vector<bool> isPrime(N+1, true);

    isPrime[0] = false;
    isPrime[1] = false;

    for(int i = 2; i * i <= N; i++){
        if(isPrime[i]){
            for(int j = i * i; j <= N; j = j + i){
                isPrime[j] = false;
            }
        }
    }

    for(int i = 2; i <= N; i++){
        if(isPrime[i] == true){
            primes.push_back(i);
        }
    }
    
}

int countSumN(int N, vector<int> primes, int smallestGreaterPrime) {
    vector<int> dp(N + 1, 0);
    dp[0] = 1; 
        
   
    for (int prime : primes) {
        if(prime==N) continue;
        for (int j = prime; j <= N; ++j) {
            dp[j] = (dp[j] + dp[j - prime])%smallestGreaterPrime;
        }
    }


    return dp[N];
}

bool isPrime(int num) {
    if (num <= 1) return false; 
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false; 
    }
    return true;
}


int findNext(int N) {
    int next = N + 1; 
    while (!isPrime(next)) {
        next++;
    }
    return next;
}

int main(){

    int N;
    cin >> N;

    if (N <= 1) {
        cout << 0 << endl;
        return 0;
    }

    vector<int> primes;

    fillVector(N, primes);
    // cout<<"array :"<<endl;
    //  for(int i = 0; i < primes.size(); i++){
    //     cout<<primes[i]<<endl;
    //  }

    int smallestGreaterPrime = findNext(N);

    int sum = countSumN(N, primes, smallestGreaterPrime);

   
   
    int ans = sum % smallestGreaterPrime;

    // cout<<"sum and P"<<endl;
    //  cout << sum << endl;
    //  cout << smallestGreaterPrime << endl;

    cout << ans << endl;

    return 0;
}
