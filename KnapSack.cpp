/* 
 * ************************************************
 *    Sourav Sanyal 
 *    A02262314
 *    Bridge Lab
 *    Utah State University
 *    MS in Electrical and Computer Engineering
 **************************************************
 */

#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>
#include<sys/time.h>
#include<fstream>
#include<stdlib.h>

using namespace std;

//Recursive Function

bool KnapRecursive(const int& n, const int& L1, const int& L2, const vector<int>& s) {

	//base cases

	if ( L1 < 0 || L2 < 0 ) return false ;

	if ( L1 == 0 && L2 == 0 ) return true ;

	if ( n == 0 ) return false ;

	// problem construction

	return KnapRecursive( (n -1 ) , (L1 - s[n]) , L2 , s ) or KnapRecursive( (n-1) , L1 , (L2 - s[n]) , s ) or KnapRecursive( (n-1) , L1 , L2 , s ) ;

}


// Memoized Function


bool KnapMemo(const int& n , const int& L1, const int& L2, const vector<int>& s){

	//create cache to store intermediate function calls

	bool cache[n + 1][L1 + 1][L2 + 1];

	//create book-keeping array to keep track of cache entries

	bool cacheValid[n + 1][L1 + 1][L2 + 1];

	//base cases


	if ( L1 < 0 || L2 < 0 ) return false ;


	if ( L1 == 0 && L2 == 0 ) {


		for ( int i = 0 ; i <= n ; ++i ) {

			cache[i][0][0] = true ;

			cacheValid[i][0][0] = true ;

		}
	}


	if ( n == 0 ) {

		for ( int i = 1 ; i <= L1 ; ++i ) {
	
			for ( int j = 1 ; j <= L2 ; ++j ) {

				cache[0][i][j] = false ;

				cacheValid[0][i][j] = true ;

				}

			}

	}

	//problem instance to solution instance mapping

	 if ( cacheValid[n][L1][L2] ) return cache[n][L1][L2] ;

		
	 else {
		cache[n][L1][L2] = cache[n-1][L1 -s[n]][L2] or cache[n-1][L1][L2 -s[n]] or cache[n-1][L1][L2] ;

		cacheValid[n][L1][L2] = true ;	

		return cache[n][L1][L2] ;  

	
	       }	
}	

//function to calculate wall clock time

double get_wall_time()

{

	  struct timeval time;

	  if (gettimeofday(&time,NULL)) {

        	 return 0;

          	 }

          return ((double)time.tv_sec + (double)time.tv_usec * .000001)*1000;

 }


//Probelm generator to create a list of n integers within range 0 to m-1. These will be used as sizes of n objects


vector<int> ProblemGenerator ( int n , int m ) {

	vector<int> list ;

	for ( int i = 0 ; i < n ; ++i ) {

	list.push_back( 1 + rand()%(m+1)) ;

	}

	return list ;

}




 

int main(){

	int L1 = 100 ; 

	int L2 = 100 ; 

	srand(time(NULL));

	cout << "Begin calculating Recursive Call Complexity"<<endl;

	ofstream file ;

	//creates a file to recors KnapRecursive runtime stats

	file.open("KnapRecursive_stats.txt");

	pair<int,double> recurr ;

	vector<pair<int,double> > rstats;

	

	for ( int n = 10 ; n <201 ; n += 10){

		double time = 0;

		for ( int i = 0 ; i < 10 ; ++i ) {

			
			vector<int> size = ProblemGenerator(n,50);

			double wall0 = get_wall_time();

			cout<<" n , iter = "<<n<<"\t,\t"<<i<<endl;

			KnapRecursive(n,L1,L2,size);

			double wall1 = get_wall_time();

			double wall = wall1 -wall0 ;

			time += wall ;

			}

			time = 0.1*time ;

			recurr = make_pair(n,time);

			rstats.push_back(recurr);

	}	


	vector<pair<int,double> >::iterator i1 ;

	file<<"n\t"<<"Execution Time"<<endl;

	for ( i1 = rstats.begin(); i1 != rstats.end() ; i1++ ) {

		file << i1->first << "\t" << i1->second <<endl;

	}


	file.close();

	

	cout<< " Done calculating Recursive Call Complexity "<<endl;

	cout << " Begin calculating Memoization Call Complexity "<<endl;

        ofstream file1 ;

// creates a file to record KnapMemo runtime stats

        file1.open("KnapMemo_stats.txt");

        pair<int,double> memo ;

        vector<pair<int,double> > mstats;

     

        for ( int n = 10 ; n <201 ; n += 10){

                double time = 0;

                for ( int i = 0 ; i < 10 ; ++i ) { 

     
                        vector<int> size = ProblemGenerator(n,50);

                        double wall0 = get_wall_time();

                        cout<<" n , iter = "<<n<<"\t,\t"<<i<<endl;

                        KnapRecursive(n,L1,L2,size);

                        double wall1 = get_wall_time();

                        double wall = wall1 -wall0 ;

                        time += wall ;

                        }   

                        time = 0.1*time ;

                        memo = make_pair(n,time);

                        mstats.push_back(memo);

	}


	vector<pair<int,double> >::iterator i2 ;

	file1<<"n\t"<<"Execution Time"<<endl;

	for ( i2 = mstats.begin(); i2 != mstats.end() ; i2++ ) {

       		 file1 << i2->first << "\t" << i2->second <<endl;

	}


	file1.close();



	cout<< " Done calculating Recursive Call Complexity "<<endl;


	return 0 ;

	}
	
				
