//ACCEPTED

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
using namespace std;

struct Point {
    long long x;
    long long y;
};

bool compareElems(const Point &p1, const Point &p2) {
    if (p1.x == p2.x) {
        return p1.y < p2.y;
    }
    return p1.x < p2.x;
}

bool compareElemsY(const Point &p1, const Point &p2) {
    if (p1.y == p2.y) {
        return p1.x < p2.x;
    }
    return p1.y < p2.y;
}

int main() {
  int n;
  cin>>n;
  vector<Point> elems(n);
  vector<Point> elems2(n);
  

  for (int i = 0; i<n;i++ ){
    long long x;
    long long y;
    cin>>x;
    cin>>y;
    elems[i]={x,y};
    elems2[i]={x,y};
  }
  sort(elems.begin(), elems.end(), compareElems);
  sort(elems2.begin(), elems2.end(), compareElemsY);

  long long minX = elems[0].x;
  long long maxX = elems[n-1].x;
  
  long long minY = LLONG_MAX, maxY = LLONG_MIN;
  for (int i = 0; i < n; i++) {
        minY = min(minY, elems[i].y);
        maxY = max(maxY, elems[i].y);
   }


  long long bigS = (long long) (maxY -minY) *(maxX -minX);


  vector<long long> sizes(n,0);
  vector<long long> sizes2(n,0);
  long long curMinX=elems2[0].x;
  long long curMaxX= elems2[0].x;
  long long curMinY=elems[0].y;
  long long curMaxY= elems[0].y;

  vector<Point> elemsMax(n);
  vector<Point> elemsMin(n);
  vector<Point> elemsMax2(n);
  vector<Point> elemsMin2(n);

  for(int i = 0 ; i< n ;i++){
    curMinY = min(curMinY, elems[i].y);
    curMaxY = max(curMaxY, elems[i].y);
    elemsMax[i]={elems[i].x,curMaxY };
    elemsMin[i]={minX,curMinY };
    long long s1 = (long long) (curMaxY - curMinY) * (elems[i].x-minX);
    sizes[i]=s1;
  }
  for(int i = 0 ; i< n ;i++){
    curMinX = min(curMinX, elems2[i].x);
    curMaxX = max(curMaxX, elems2[i].x);
    elemsMax2[i]={curMaxX,elems2[i].y};
    elemsMin2[i]={curMinX ,minY };
    long long s1 = (long long) (elems2[i].y- minY) * (curMaxX-curMinX);

    sizes2[i]=s1;
  }

  curMinY=elems[n-1].y;
  curMaxY= elems[n-1].y;
  curMinX=elems2[n-1].x;
  curMaxX= elems2[n-1].x;

  for(int i = n-1 ; i> 0 ;i--){
    curMinX = min(curMinX, elems2[i].x);
    curMaxX = max(curMaxX, elems2[i].x);
    long long s1 = (long long) (maxY-elems2[i].y) * (curMaxX-curMinX);
    
    if(elemsMax2[i-1].y == elems2[i].y){ 
        if(elemsMax2[i-1].x>curMaxX){
            if(elemsMin2[i-1].x>curMaxX ){
                sizes2[i-1]+=s1;
            }else{
                sizes2[i-1]=LLONG_MAX;
            }
        }
        else if(elemsMax2[i-1].y<curMaxX ){
            if(elemsMax2[i-1].y<curMinX ){
                sizes2[i-1]+=s1;
            }else{
                sizes2[i-1]=LLONG_MAX;
            }
        }
        else{ 
            sizes2[i-1]=LLONG_MAX;
        }
    }
    else{
      sizes2[i-1]+=s1;
    }  
  }

  for(int i = n-1 ; i> 0 ;i--){
    curMinY = min(curMinY, elems[i].y);
    curMaxY = max(curMaxY, elems[i].y);
    long long s1 = (long long) (curMaxY - curMinY) * (maxX - elems[i].x);
    if(elemsMax[i-1].x == elems[i].x){  
        if(elemsMax[i-1].y>curMaxY){
            if(elemsMin[i-1].y>curMaxY ){
                sizes[i-1]+=s1;
            }else{
                sizes[i-1]=LLONG_MAX;
            }
        }
        else if(elemsMax[i-1].y<curMaxY ){
           
            if(elemsMax[i-1].y<curMinY ){
                sizes[i-1]+=s1;
            }else{
                sizes[i-1]=LLONG_MAX;
            }
        }
        else{ 
            sizes[i-1]=LLONG_MAX;
        }
    }
    else{
      sizes[i-1]+=s1;
    }  
  }

  long long minSize=sizes[1];
  for(int i = 1; i < n;i++){
      minSize = min(minSize, sizes[i]);
  }
  for(int i = 0; i < n;i++){
    
    minSize = min(minSize, sizes2[i]);
  }
  cout<<bigS - minSize <<endl;
  
  return 0;
  
  
}