#include <cmath>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;


void read(double* , int& , string );
void filter(double* const , int& );
void write(double* const, int&, string );

int main ()
{
  int N;
  int M;
  cout << "# of lines in file ="; cin >> N;  
  double* const p = new double[N];		//dynamic allocation
  const string filename = "noisy.txt";
  const string writefile = "filtered.txt";
  string condition;

  cout << "Data read out of file " << filename << "." << endl;
  read(p,N,filename);			//read from file and store in array with address p
  
  
  
  
  /*	Im Folgendem soll abgefragt werden wie oft die Funktion "filter" benutzt werden soll. Es funktioniert alles auch ohne diese Abfrage. 					 */
  /*										 												*/
  cout << "You can use the filter function more than once. When it's used more the Amplitude of your main signal is going to be damped too. Damping increases with how often the function is going to be used." << endl;
  cout << "If wanted to use the filter function more than once, type Y else N: "; cin >> condition;
  
  if (condition == "Y")
  {
      cout << "How often use filter function:"; cin >> M;
      for(int j=0;j<M;j++)
      {
	filter(p,N);
      }
  }
  
  else{
  filter(p,N);				//use function "filter" on array p
  }
  
  /****************************************************************************************************************************************************************************/
  
  
  cout << "Filtered data saved in "<<writefile<< "." << endl;
  write(p,N,writefile);				//write the filtered data in filtered.txt
  

  
  delete[] p;				//free up memory
  return 0;
}




void read(double* const p, int& N, string filename){
  
  ifstream in(filename.c_str());		//input file stream 
 
  for(int i=0;i<N;i++){
    in >> p[i];
  }
  in.close();				//close input file stream
}




void filter(double* const p, int& N){
  double start = p[0];			//for periodicity, g[N]=(p[N-1]+p[N]+p[0])/3
  double begin = p[0];			
  double temp = p[1];
  double end = p[N-1];			//like for start


  p[0]=(end+begin+temp)/3;		//for p[0]

  
  for(int i=1;i<N-1;i++){
    temp =p[i];
    p[i]=(begin+temp+p[i+1])/3;
    begin = temp;
    }

  p[N-1]=(begin+end+start)/3;  	//for p[N]

  

}



void write(double* const p, int& N, string writefile){
  ofstream out(writefile.c_str());
  for(int i=0;i<N;i++){
    out<<p[i]<<endl;
  }
  out.close();
}