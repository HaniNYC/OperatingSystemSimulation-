/*HANI ABOUDESHISHA                       CSCI340                     ASSIGNMENT 1       OPERATING SYSTEM DEMO*/
/* this program will simulate the CPU handling of processes and intruptions from users or processes
++the program simulate the processes life cycle and its movemenet to different system and devices queues as a result of a signal or intruption
++the program contains three vectors that contain the devices - hard disks , printers and CD/RW
++each device contain its own queue that along with the ready queues will be used to simulate a process life cycle
++each device has its own ID , also each process has its own PCB
++the program contains four classes, one for the process and one for each device
++the program contains three global variables - number of devices- since it is needed to be avilable for all functions
++the main function contains  two functions only, one for system setting mode and the other for running mode */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include<cmath>
#include<ctime>
using namespace std;
int n,m,k;  // n for hard drives , m for printers, k for cds
double TimeSlice=0;  /// <-------------time slice for RR algo - defined by user------
double total_CPU_Times=0;  /// <------------------for all processes
int totalProcesses =0;
int pageSize=0;
int TotalMemorySize=0;
int FreeMomery =0;
int TotalUsedFrames=0;
int FreeFrames=0;
int framSize=0;
int AllPagesCount=0;
int AllFramesCounts=0;
int maxProcessSize=0;
int offest=0;
int frameBits=0;
int pagesBits=0;
int maxPagesPerProc=0;
double AllProcessesBurstTime=0.0;  /// <------------------for all processes
int CompletedProcesses =0;      /// <----------through t,d,c,p only 
double SysAvgBurstTime;
void set_SysAvgBurstTime( double x, int y){
       if ( y!=0) SysAvgBurstTime= x/y;
       else SysAvgBurstTime= 0;} 
double  get_SysAvgBurstTime(){ return SysAvgBurstTime;}
//===========================================================================================================================
class Frames{
      public:
             Frames();
             Frames(int);
             ~Frames();
             bool occupied;
             void set_frameNu(int);
             int get_frameNu();
             void set_occupied_by_processId( int);
             int get_occupied_by_processId();
      private:
             int frameNu;
             int occupied_by_processId;
             };
//============================================================================================================================//
class Process{                                  /// Processes class, contains more than needed functions/data// for experimental and developement
      public:
             Process();
             ~Process();
             Process( int);
             void setID(int);
             int getID();
             void setType( string);   /// will be used to track the orign of a process
             string getType();
             void set_starting_memory(int);
             int get_starting_memory();
             void set_ending_memory();
             int get_ending_memory();
             void set_length(int);
             int getlength();
             void set_WRX(char);
             char get_WRX();
             void setMSR( string);
             void setMLR( string);
             string getMSR();
             string getMLR();
             void set_current_location(string);
             string get_current_location();
             void setFileName( string );
             string getFileName() ;
             void set_pTime(double);
             double get_pTime();
             void set_CylinderNum(int);
             int get_CylinderNum();
             void set_cpuV(int);
             int get_cpuV();
             double get_avgCPUtime();
              void set_ProcessBurstTime( double);
             double get_ProcessBurstTime  ();
             void set_ProcessBurstCount(int);
             int get_ProcessBurstCount();
             void set_ProcessAvgBurstTime( double , int);
             double get_ProcessAvgBurstTime(); 
             void set_ProcSize(int);
             int get_ProcSize();
             void set_framesNeeded(int);
             int get_framesNeeded();
             vector < Frames > pageTable;
             void set_logAdd( string);
             string get_logAdd();
             void set_pageNum(int);
             int get_pageNum();
             void set_pageOffset(int);
             int get_pageOffset();
      private:
              int ID;
              double pTime;
              int cpuV;
              double avgCPUtime;
              double ProcessBurstTime;//<------------------
              int ProcessBurstCount;//<-----------------
              double ProcessAvgBurstTime;//<-----------------
              int ProcSize;
              int framesNeeded;
              string type;
              int starting_memory;
              int ending_memory;
              int length;
              char WRX;
              string current_location;
              string MSR;
              string MLR;
              string fileName;
              int CylNum;
              string logAdd;
              int pageNum;
              int pageOffset;
             };
//=============================================================================================================================//
///        hard drives class , will be manipulated by a fillVector function to creat devices and stored in a vectore
class HardDrives{
      public:
             HardDrives();
             ~HardDrives();
             HardDrives( int i);  //

             queue< Process > HDqueue;
             int number_of_items_in_Hd_Queue();
             bool is_empty();
             void print_HDqueue();
             int getHD_ID();
             string name;
             string getName();
             vector<Process> HDvector;
             void set_headPosition(int);
             int get_headPosition();
             void set_CylinderNUM(int);
             int get_CylinderNUM();
             
      private:
              int HD_ID;
              int headPosition;
              int CylinderNUM;

};
//-------------------------------------------------------------------------------------------------------------------------//
class Printers{            /// same as hard drive class
      public:
             Printers();
             ~Printers();
             Printers( int i);  //
             queue< Process > PRqueue;
             int number_of_items_in_PR_Queue();
             bool is_empty();
             void print_PRqueue();
             int getPR_ID();
             string name;
             string getName();
      private:
              int PR_ID;
};
//--------------------------------------------------------------------------------------------------------------------------//
class CD{                 ///same as hard drive class
      public:
             CD();
             ~CD();
             CD( int i);  //
             queue< Process > CDqueue;
             int number_of_items_in_CD_Queue();
             bool is_empty();
             void print_CDqueue();
             int getCD_ID();
             string name;
             string getName();
      private:
              int CD_ID;
};
//--------------------------------------------------------------------------------------------------------------------------
    
///////////////////////////////////////////General Functions///////////////////////////////////////////
string append( string str, int i);
void fillVector(vector<HardDrives>&,int ); /// to creat and store devices
void fillVector(vector<Printers>&, int );
void fillVector(vector<CD>& ,int );
void printVector( vector <HardDrives>&);
void printVector(  vector <Printers>&);     /// to acess and print devices
void printVector(  vector <CD>&);
void SeysGenMode();                           // first main function , will be used to set up system
void runningMode();                            // second main function , we be used to creat and move processes
bool cmp (  Process s1 ,  Process s2);

//------------------------------------------------------------------------------------------------------
vector <Printers> PRvec;          // vector of devices will be copied here for functions access
vector <HardDrives> HDvec;
vector <CD> CDvec;
vector <Frames> framesV;
vector< Frames > freeFramesV;



////***********************************************************************************************//////
////////////////////////////////////////// M A I N //////////////////////////////////////////////////////
int main(){

 SeysGenMode();                                       // setting system
 runningMode();                                       // running mode



    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////  Function Definitions////////////////////////////////////////////////
string append( string str, int i){
    stringstream s;                                   // append char to int
    s <<  str << i;
    return s.str();
}
//---------------------------------------------------------------------------------------------------------//
void fillVector(vector<HardDrives> & HDVec,int p){
     for (int i=0; i< p; i++)
     {
       HardDrives HD(i);
       HD.name = append("d",i);
       cout<<" How Many Cylinders are in "<< HD.name <<" ?" <<endl; 
       int n; 
       stringstream hd;
       string input_hd;
       cin >> input_hd;
       hd << input_hd;
       hd>>n;
   if (hd.fail()){
      cout<< "please enter a number"<<endl;
      cin >> n;}
      while ( n <= 0){
            cout <<" please enter a valid number !"<<endl;
            cin>> n;}
       HD.set_CylinderNUM( n);
       
       HDVec.push_back( HD);
       cout<<endl;
       }
       HDvec = HDVec;
}
 //----------------------------------------------------------------------------------------------------------//
 void fillVector(vector<Printers> & PRVec,int p){
     for (int i=0; i< p; i++)
     {
       Printers pr(i);
       pr.name = append("p",i);
       PRVec.push_back( pr);
       cout<<endl;
       }
       PRvec=PRVec;
}
 //----------------------------------------------------------------------------------------------------------//
 void fillVector(vector<CD> & CDVec,int p){
     for (int i=0; i< p; i++)
     {
       CD cd(i);
       cd.name = append("c",i);
       CDVec.push_back( cd);
       cout<<endl;
       }
       CDvec=CDVec;
}

//--------------------------------------------------------------------------------------------------------//
bool isPowerOfTwo (unsigned int x)
{
 int counterOFS=0;    
 while (((x % 2) == 0) && x > 1) /* While x is even and > 1 */
  { x /= 2;
   isPowerOfTwo ( x);
   counterOFS++;
   }
 if (x == 1){ 
       offest = counterOFS; 
       return true;}
 else{ return false;}
}
//----------------------------------------------------------------------------------------------------------//
bool isDividable (unsigned int x,unsigned int y)
{
 if (((x % y) == 0) && x > 1&& x>y) /* While x is even and > 1 */
 return true;
 else{ return false;}
}
//--------------------------------------------------------------------------------------------------------//
int find_how_many_bits(int decimal){
   
    
    int remainder = decimal % 2;
    if (decimal < 1)
        
        return frameBits;
    else
    frameBits++;
    find_how_many_bits(decimal / 2);
  
   
    
} 
//-----------------------------------------------------------------
int find_how_many_Pages_bits(int j){ // j is # pages
if (j<=2){ return 1;}
if (j> 2 && j <=4 ){ return 2;}
if (j> 4 && j <=8) {return 3;}
if (j > 8 && j<=16 ){ return 4; }
if (j > 16 && j<=32 ){ return 5; }
if (j > 32 && j<=64 ){ return 6; }
if (j > 64 && j<=128 ){ return 7; }
if (j > 128 && j<=256 ){ return 8; }   
if (j > 256 && j <= 512){ return 9;}
if (j >512  && j<=1024 ){ return 10; }  
if (j >1024  && j<=2048){ return 11; } 
if (j >2048 && j<=4096 ){ return 12; }
else 
return   
 16;   
} 
//---------------------------------------------------
int set_max_pages_per_process( int e, int q){
                           if (e % q ==0) { return e/q ;}
                           else 
                           return (e/q)+1;
                           }
//----------------------------------------------------------------------------------------------------------//
void set_pages_bits(int x , int y){
     int z;
      z=( x/y)+1;
     find_how_many_Pages_bits(z) ;
     }
//----------------------------------------------------------------------------------------------------------//
string DecToBin(int number)  // to convert the frame number from decimal to binary then contaciate it to offset
{
    if ( number == 0 ) return "0";
    if ( number == 1 ) return "1";

    if ( number % 2 == 0 )
        return DecToBin(number / 2) + "0";
    else
        return DecToBin(number / 2) + "1";
} 
//----------------------------------------------------------------------------------------------------------//
void printVector(  vector <HardDrives>& newHDvec){
    cout<< " system has set up the following hard drives :" <<endl;
    unsigned int size = newHDvec.size();
    for ( int i=0; i< size ; i++){
    cout << " Name: " << newHDvec[i].getName();
    cout <<"      " <<" ID  : "  << newHDvec[i].getHD_ID()<<endl;

    }


}
//----------------------------------------------------------------------------------------------------------//
void printVector(  vector <Printers>& newHDvec){
    cout<< " system has set up the following printers :" <<endl;
    unsigned int size = newHDvec.size();
    for ( int i=0; i< size ; i++){
    cout << " Name: " << newHDvec[i].getName();
    cout <<"      " <<" ID  : "  << newHDvec[i].getPR_ID()<<endl;

    }

}
//----------------------------------------------------------------------------------------------------------//
void printVector(  vector <CD>& newHDvec){
    cout<< " system has set up the following CD/WR :" <<endl;
    unsigned int size = newHDvec.size();
    for ( int i=0; i< size ; i++){
    cout << " Name: " << newHDvec[i].getName();
    cout <<"      " <<" ID  : "  << newHDvec[i].getCD_ID()<<endl;

    }

}
//--------------------------------------------------------------------------------------------------------//
bool cmp (  Process s1 ,  Process s2){
  if ( s1.get_CylinderNum() != s2.get_CylinderNum()){
       return s1.get_CylinderNum() < s2.get_CylinderNum() ;
       }
   else{                                 // if both share the same cylinder, then use the id as breaker
        return s1.getID() < s2.getID() ;

        }
}
//-------------------------------------------------------------------------
bool cmp1 (  Process s1 ,  Process s2){
  if ( s1.get_ProcSize() != s2.get_ProcSize()){
       return s1.get_ProcSize() > s2.get_ProcSize() ;
       }
   else{                                 // if both share the same cylinder, then use the id as breaker
        return s1.getID() < s2.getID() ;

        }
}
//std::sort(jobPool.begin(), jobPool.end(), cmp1);  // by process size
//-----------------------------------------------------------------------------------------------------------//
//vector < process>  

//-------------------------------------------------------------------------------------------------------  //
void SeysGenMode(){
    cout<<"---SYS. GEN.--"<<endl;
    cout<<"---SETTINGS --"<<endl;
    cout<<"-------Welcome User --------"<<endl;
    cout<<" let's start by setting your system "<<endl;
    cout<< " how many hard drive you like to use "<<endl;
    stringstream s;
    string input_hd;
    cin >> input_hd;
    s << input_hd;
    s>>n;
   if (s.fail()){
      cout<< "please enter a number"<<endl;
      cin >> n;}
      

  //-----------------------------------------------------
    cout<< " how many printers you like to use "<<endl;
    stringstream ss;
    string input_p;
    cin >> input_p;
    ss << input_p;
    ss>>m;
   if (ss.fail()){
      cout<< "please enter a number"<<endl;
      cin >> m;}
 //-----------------------------------------------------------------
    cout<< " how many CD/WR you like to use "<<endl;
    stringstream sss;
    string input_cd;
    cin >> input_cd;
    sss << input_cd;
    sss>>k;
   if (sss.fail()){
      cout<< "please enter a number"<<endl;
      cin >> k;}
//----------------------------------------------------------------
    vector <HardDrives> VecHD;
    vector <Printers>  VecPR;
    vector  <CD>       VecCD;
    fillVector( VecHD,n);
    fillVector( VecPR,m);
    fillVector( VecCD,k);
    printVector( VecHD);
    cout <<endl;
    printVector( VecPR);
    cout <<endl;
    printVector( VecCD);

    cout<<" please enter time slice in ms"<<endl;
    cout<<">";

    stringstream ssss;
    string input_ts;
    cin >> input_ts;
    ssss << input_ts;
    ssss>>TimeSlice;
   if (ssss.fail()){
      cout<< "please enter a number"<<endl;
      cin >> TimeSlice;}
   // cin>> TimeSlice;       ///  needs error check against 0, <0
    while ( TimeSlice <= 0){
          cout<<" please enter a valid time: "<<endl;
          cout<<">";
          cin>> TimeSlice;
          }
    cout<<" cpu time slice is "<<TimeSlice<<" m.sec."<<endl;
    //------------------------------Memory Mangement---------------------------------//
    cout <<" Alright, lets set up the system memory "<<endl;
    cout<<"----------------------------------------"<<endl;
    cout<< " please enter logical page size "<<endl;
    int pageSz;
    cin>> pageSz;
    while (!isPowerOfTwo(pageSz)){
          cout<<" please enter a valid number"<<endl;
          cin>>pageSz;
          }
    
    cout <<" please enter total memory size in words "<<endl;
    int memorySz;
    cin >> memorySz;
    while ( ! isDividable( memorySz, pageSz)){
          cout<<" please enter a valid number Hint: must be divsible by page Size"<<endl;
          cin>>memorySz;
          }
    TotalMemorySize=memorySz;
    FreeMomery = memorySz;
    AllFramesCounts = memorySz/ pageSz;
    framSize=pageSz;
    pageSize=pageSz;   
    FreeFrames=AllFramesCounts;   
    cout<<" please enter max, process's size in words "<<endl;
    cin >> maxProcessSize;
    while ( maxProcessSize<=0 || maxProcessSize >= memorySz){
          cout<<" please enter a valid size "<<endl;
          cin>> maxProcessSize;
          }
     maxPagesPerProc  =set_max_pages_per_process( maxProcessSize,pageSize);   
    //set_pages_bits(maxProcessSize , pageSize);
     pagesBits=find_how_many_Pages_bits(maxPagesPerProc);    
    //frameBits=find_how_many_bits(AllFramesCounts);      
    cout<<" Ok, you have "<<AllFramesCounts << " frames, each has a size of "<<framSize<<" words to play with !!"<<endl;
    cout << " the offset is: " << offest << " bits"<<endl;
  //  cout <<" you will need: "<< frameBits << " bits for frames # "<<endl;
    frameBits = find_how_many_Pages_bits(AllFramesCounts);
 //  frameBits = (log(AllFramesCounts)/log(2))+1;
   cout <<" You will need: "<< frameBits << " bits for frames # "<<endl;
   cout <<" And "<<endl; 
   cout <<" You will need: "<< pagesBits <<" bits for pages#"<<endl; 
   //--------------------------------------------------------------------
   for ( int i=0; i < AllFramesCounts; i++){
       Frames fr(i);
       fr.set_frameNu(i);
       framesV.push_back(fr);
       } 
   freeFramesV = framesV;
 //  for ( int i=0; i < freeFramesV.size(); i++){
     //  cout << freeFramesV[i].get_frameNu()<<endl;}
       
}
///==========================================================================================================//

////////////////////////////////////////////////////////////
void runningMode(){

    bool CPU_is_free = true;       // swithch
    queue<Process> cpuQueue;
    queue<Process> tempQueue;
    queue<Process> readyQueue;
    queue <Process> backup;
    vector <Process> JobPool;
    vector <Process> orderedJobPool;
 /*   void clear_backup(){
         while (!backup.empty())
               {
               backup.pop();
               }
         }*/
   // int PRC=0;  //printers counter
    int PC=0;                  // process counter
    cout<<" Let's Start, please enter a process 'A' to begin "<<endl;
    string action;
    string input;  
    cout<<" >>";
    cin >> input;

                while (input!="A")
                {
                     cout<<" please enter a valid process 'A' to begin "<<endl;
                     cout<<" you must start with a process , so ..." <<endl;
                     cin>> input;
                     }
                if (input== "A")
                 {
                Process p(PC);           
                int pz;            
                cout<< " please enter process size "<<endl;
                cin >>pz;    
                while ( pz>  maxProcessSize || pz  >  TotalMemorySize|| pz <=0){
                      cout <<" please enter a valid size"<<endl;
                      cin>> pz;}
                 p.set_ProcSize(pz);
                 int FN;
                 if( p.get_ProcSize()% pageSize==0){  FN = p.get_ProcSize()/ pageSize;}
                 else if (p.get_ProcSize()% pageSize!=0) {FN= (p.get_ProcSize()/ pageSize)+1;} 
                      p.set_framesNeeded (FN); 
                 if ( p.get_framesNeeded() > FreeFrames){       
               // if ( p.get_ProcSize() >  FreeMomery) {
                     JobPool.push_back( p);
                     cout<< " process is in job pool "<<endl;
                     std::sort(JobPool.begin(), JobPool.end(), cmp1);
                     }
                else if ( p.get_framesNeeded() <= FreeFrames){
               // FreeMomery = FreeMomery- p.get_ProcSize(); 
                //----------------------------------------------------
                 int f =p.get_framesNeeded();
             
                    for ( int i =0; i < freeFramesV.size()&& f >0; i++){  
                    if ( freeFramesV[i].occupied == false){
                         freeFramesV[i].set_frameNu(i);
                         freeFramesV[i].set_occupied_by_processId(p.getID());///<----------------------------------------
                         p.pageTable.push_back(freeFramesV[i]);
                         f--;
                         FreeFrames--;
                         FreeMomery = FreeMomery - pageSize;
                        // freeFramesV[i].set_occupied_by_processId(p.getID());
                         freeFramesV[i].occupied = true;
                         cout<< f<<endl;
                        //freeFramesV.erase (freeFramesV.begin()+i);  // it is better to just mark it as in line above
                        }  // an keep fram in vector but with bool marked as occupied
                        }
                        readyQueue.push(p);
                        }
                //----------------------------------------------------           
                cout<<" here we go, we had a process in a ready queue "<<endl;
                cout<<" this process has moved immeditally to the CPU because it was free"<<endl;
                cout<<" it has been asssigned the following frames "<<endl;
                for ( int i =0; i< p.pageTable.size();i++){
                    cout <<p.pageTable[i].get_frameNu()<<endl;}
              //  Process p(PC);
                PC++;
                totalProcesses= PC;
                
              //  readyQueue.push(p);
                p.setType("User");

                }
                 if ( CPU_is_free  )
                {
                 cpuQueue.push(readyQueue.front())  ;
                 cout<<" process ID's: "<< cpuQueue.front().getID()<<" is occupying CPU" <<endl;
                 cpuQueue.front().setType("Ready Queue");
                 cpuQueue.front().set_cpuV(1);
                 CPU_is_free = false;
                 readyQueue.pop();

                 }

        cout<<" now we are ready for some actions! "<<endl;
        cout<<"===================================="<<endl;
        cout<<" --RUNNING MODE-- "<<endl;
        cout<<" Now, please enter an action"<<endl;
        cout<<" please enter :"<<endl;
        cout<<"'A' -----to add a process" << endl;
        cout<<"'p' -----to call printer job"<<endl;
        cout<<"'d'------to call harddrive job"<<endl;
        cout<<"'c'------to call CD job      "<<endl;
        cout<<"'t'------to trminate a process   "<<endl;
        cout<<"'CapS'  to terminate a process"<<endl;
        cout<<"'S+letter' to print queues  "<<endl;
        cout<<"'K# To kill a process#  "<<endl;
 //label1:
    while (true)
    {
    cout<<" >> ";
    cin >> action;
    while ( action !="A" && action !="S" && action !="t" && action[0]!='K' && action!="T"&& action[0] !='p' && action[0] !='P' && action[0] !='d' && action[0] !='D' && action[0] !='c' && action[0] !='C')
    {
          cout << " please enter a valid action "<<endl;
          cin >> action;
    }
 //------------------------------------------CASE 1---------------------------------------------------
    if ( action == "A"){
                Process p(PC);
                PC++;
                totalProcesses = PC;
                p.setType(" User");
                //----------------------------------
                int pz;            
                cout<< " please enter process size "<<endl;
                cin >>pz;    
                while ( pz>  maxProcessSize || pz  >  TotalMemorySize|| pz <=0){
                      cout <<" please enter a valid size"<<endl;
                      cin>> pz;}
                 p.set_ProcSize(pz);
                 int FN;
                 if( p.get_ProcSize()% pageSize==0){  FN = p.get_ProcSize()/ pageSize;}
                 else if (p.get_ProcSize()% pageSize!=0) {FN= (p.get_ProcSize()/ pageSize)+1;} 
                      p.set_framesNeeded (FN); 
                if ( p.get_framesNeeded() > FreeFrames){        
               // if ( p.get_ProcSize() >  FreeMomery) {
                     JobPool.push_back( p);
                     cout<< " process is in job pool "<<endl;
                     std::sort(JobPool.begin(), JobPool.end(), cmp1);
                     }
                  else if ( p.get_framesNeeded() <= FreeFrames){
                //FreeMomery = FreeMomery- p.get_ProcSize();
              //  FreeFrames= FreeFrames- p.get_framesNeeded();  
                //---------------------------------
                int f =p.get_framesNeeded();
             
                    for ( int i =0; i < freeFramesV.size()&& f>0; i++){  
                    if ( freeFramesV[i].occupied == false){
                         freeFramesV[i].set_frameNu(i);
                         freeFramesV[i].set_occupied_by_processId(p.getID());////<-------------------------------
                         p.pageTable.push_back(freeFramesV[i]);
                         f--;
                         FreeFrames--;
                         FreeMomery = FreeMomery - pageSize;
                       //  freeFramesV[i].set_occupied_by_processId(p.getID() );
                         freeFramesV[i].occupied = true;
                        //freeFramesV.erase (freeFramesV.begin()+i);  // it is better to just mark it as in line above
                        }  // an keep fram in vector but with bool marked as occupied
                        }
                    cout<<" it has been asssigned the following frames "<<endl;
                    for ( int i=0; i< p.pageTable.size();i++){
                    cout <<p.pageTable[i].get_frameNu()<<endl;}
                    
                      //  }
                //---------------------------------
                
                readyQueue.push(p);
                }
             //   cout<<" process ID "<< PC-1 <<" is in ready queue"<<endl;
              //  cout<<" readyQueue front process ID is :"<<readyQueue.front().getID()<<endl;
              //  cout<<" CPU is equippied by process ID :"<<cpuQueue.front().getID()<<endl;  // for debbging

                }


   //-------------------------------------CASE 2---------------------------------------------------

    else if (action == "t"){
          if(CPU_is_free && cpuQueue.empty()){
                 cout<<" there is no process in CPU to terminate"<<endl;
                // throw -1;
                 }


                 else if( !CPU_is_free){
                  double ptmt;
                  cout<< " please enter current processing time: "<<endl;
                  cout<<">";
                  stringstream strt;
                  string input_ptmt;
                  cin >> input_ptmt;
                  strt << input_ptmt;
                  strt>>ptmt;
                  if (strt.fail()){
                  cout<< "please enter a number"<<endl;
                  cin >> ptmt;}
                  while (ptmt <=0 || ptmt > TimeSlice)
                  {
                      cout<<" please enter a valid processing time " <<endl;
                      cout<<">";
                      cin>>ptmt;

                  }
                  total_CPU_Times += ptmt;

                  cpuQueue.front().set_pTime(ptmt);
                  /*-------------------------*/
                  cpuQueue.front().set_ProcessBurstTime(cpuQueue.front().get_pTime());
                  cpuQueue.front().set_ProcessBurstCount(1);
                  cpuQueue.front().set_ProcessAvgBurstTime(cpuQueue.front().get_ProcessBurstTime(),cpuQueue.front().get_ProcessBurstCount());
                  AllProcessesBurstTime += cpuQueue.front().get_ProcessBurstTime();
                  CompletedProcesses++;
                  set_SysAvgBurstTime( AllProcessesBurstTime,CompletedProcesses);
                  /*-------------------------*/
                  //-----------------------------------------------------------------------------------------------
                      int aa = cpuQueue.front().getID(); 
                      
                      for ( int j=0; j< freeFramesV.size() ;j ++){
                        //  cout <<"++++++++++++++"<<endl;
                        //  cout <<freeFramesV[j].get_occupied_by_processId()<<endl;
                          if( freeFramesV[j].get_occupied_by_processId()== aa){
                              freeFramesV[j].occupied = false;
                              FreeFrames++;
                              FreeMomery = FreeMomery + pageSize;
                              cout<<"frame number : "<<freeFramesV[j].get_frameNu()<<" is now free "<<endl; 
                            //  FreeMomery += pageSize;
                            }
                          //  else { cout<<" skipped"<<endl;}
                            }
                                                                                      
                  
                  
                  //--------------------------------------------------------------------------------------------------
                //  cpuQueue.front().set_avgCPUtime(  cpuQueue.front().get_pTime, cpuQueue.front().get_cpuV);
                 cout<<" The following process has been terminated"<<endl;
                 cout<<" Process ID ||" << setw(12)<< " Total CPU time ||"<< setw(12)<< "Avg. Proc. Time|| "<<"AVG Burst Time "<<endl;
                 cout<<"---------------------------------------------------------------------------"<<endl;

                 cout<<setw(9)<<cpuQueue.front().getID() <<setw(16)<<cpuQueue.front().get_pTime()<<setw(16) <<cpuQueue.front().get_avgCPUtime()<<setw(12)<<cpuQueue.front().get_ProcessAvgBurstTime()<<endl;
                 cout<<"---------------------------------------------------------------------------"<<endl;
                 cout <<"System's Avg.CPU Time(ALL Processes)         : " << total_CPU_Times/totalProcesses<<" ms/process"<<endl;
                 cout <<"System Avg Burst Time(Completed Processes) is: " << get_SysAvgBurstTime() <<" ms/completed process"<<endl;
                  cpuQueue.pop();
                  CPU_is_free = true;
                  //-------------------------------------------------------
                  if ( JobPool.size()> 0 ){
                       for ( int j=0; j<JobPool.size(); j++){
                        if ( JobPool[j].get_framesNeeded()<= FreeFrames ){  // you need to make it by frames
                             //----------------------------------------------------
                        int f =JobPool[j].get_framesNeeded();
                     //   while (f >0){
                        for ( int i =0; i < freeFramesV.size() && f >0; i++){  
                        if ( freeFramesV[i].occupied == false){
                          freeFramesV[i].set_frameNu(i);   
                         freeFramesV[i].set_occupied_by_processId(JobPool[j].getID());  ////////////////<-------------------    
                         JobPool[j].pageTable.push_back(freeFramesV[i]);
                         f--;
                      //   freeFramesV[i].set_occupied_by_processId(JobPool[j].getID() ); // MAKE SURE !!!!!!
                          FreeMomery = FreeMomery - pageSize;
                         FreeFrames--;
                         freeFramesV[i].occupied = true;
                        //freeFramesV.erase (freeFramesV.begin()+i);  // it is better to just mark it as in line above
                        }  // an keep fram in vector but with bool marked as occupied
                        }
                      //  }   YOU STILL NEED TO FREE MEMOERY AND FRAMES
                             //----------------------------------------------------
                             readyQueue.push(JobPool[j]);
                           //  FreeFrames= FreeFrames- JobPool[i].get_framesNeeded();
                          //   FreeMomery= FreeMomery -JobPool[j].get_ProcSize();
                             JobPool.erase (JobPool.begin()+j);
                             if ( JobPool.size()> 0 ){
                             std::sort(JobPool.begin(), JobPool.end(), cmp1);}
                             // earse it from vector
                             }
                             }  
                             } 
}
}
//---------------------------------------CASE 3--------------------------------------------------------

    else if (action == "p0" || action == "p1" || action=="p2" || action=="p3" || action=="p4" || action =="p5"){

       int HDN;
       char ignor;
       stringstream ss(action);
       ss>> ignor >> HDN;

       if (HDN >= m) {
             cout<< " you have only "<< m << " Printers "<<endl;
             cout<< " NOTE: counting starts at 0 "<<endl;
              // break ;
             }

       else {

                 if(CPU_is_free){
                        cout<<" there is no process in CPU to access printers"<<endl;
               //  throw -1;
                      //  break;
                 }
                else if( !CPU_is_free){

                     //  int startingMem;   // maybe string better to avoid errors
                       string startingMem;
                     //  int length;
                       string length;
                       string file_name;
                       cout<<" please enter starting memory "<<endl;
                       cin >> startingMem;
                       cout<< " please enter length "<<endl;
                       cin >> length;
                       cout<<" please enter file name "<<endl;
                       cin>> file_name;
                       cpuQueue.front().setMSR(startingMem);   // include them in def
                       cpuQueue.front().setMLR(length);
                       cpuQueue.front().setFileName(file_name);
                       cpuQueue.front().set_WRX( 'w');
                       cout<< " please enter Logical Address in Hex ! "<<endl;
                       //----------------------------
                              stringstream sshex;
                            // string input_hd;
                          //  cin >> input_hd;
                          //   hd << PHexAdd;
                          //     hd>>n;
                       //---------------------------
                       int hexad;
                       string PHexAdd;
                       cin>> PHexAdd;
                       for (int l =0; l<PHexAdd.size();l++){
                           if ( PHexAdd[l] != '0' && PHexAdd[l] != '1' && PHexAdd[l] != '2' && PHexAdd[l] != '3' && PHexAdd[l] != '4' && PHexAdd[l] != '5' && 
                           PHexAdd[l] != '6' && PHexAdd[l] != '7' && PHexAdd[l] != '8' && PHexAdd[l] != '9' && PHexAdd[l] != 'A' && PHexAdd[l] != 'a' && PHexAdd[l] != 'B'&& 
                           PHexAdd[l] != 'b' && PHexAdd[l] != 'c'&& PHexAdd[l] != 'C' && PHexAdd[l] != 'D' && PHexAdd[l] != 'd' && PHexAdd[l] != 'E' && PHexAdd[l] != 'e'&& 
                           PHexAdd[l] != 'F' && PHexAdd[l] != 'f' ){
                                      cout << " invalid hex number, try again "<<endl;
                                      cin>>PHexAdd;}}
                        cpuQueue.front().set_logAdd(PHexAdd );              
                        sshex << PHexAdd;               
                      
                    //  stringstream shex;
                        sshex>>  std::hex>> hexad;
                        cpuQueue.front().set_pageNum(hexad);
                        if ( maxPagesPerProc < cpuQueue.front().get_pageNum()){ // maybe <=
                              cout <<" INACCESSIBLE ADDRESS  !"<<endl;
                              cout << " Please enter a valid hex address" <<endl;
                              cin>>PHexAdd;
                              cpuQueue.front().set_logAdd(PHexAdd );
                              sshex << PHexAdd;
                              sshex>>  std::hex>> hexad;
                              cpuQueue.front().set_pageNum(hexad);
                              }
                    //    cout << "in dec "<<hexad<<endl;  
                       // cpuQueue.front().set_pageNum(hexad);
                    //    cout<<"page number "<< cpuQueue.front().get_pageNum()<<endl;
                        cpuQueue.front().set_pageOffset(hexad);
                    //    cout<<"page offset "<<cpuQueue.front().get_pageOffset()<<endl;
                        cout<<endl; 
                        cout << " Page Table for this process as follow: "<<endl;
                        cout<<"--------FRAMES #----------------"<<endl; 
                        for ( int i =0; i< cpuQueue.front().pageTable.size(); i++){
                            cout<< cpuQueue.front().pageTable[i].get_frameNu();
                            cout<<" || ";
                            }         
                          cout <<endl; 
                         cout<< " Their Physical Addresses Respectively Are :"<<endl;  
                         cout<<"---------------------------------------"<<endl;
                        
                         int g =cpuQueue.front().get_pageOffset();
                         for ( int i =0; i< cpuQueue.front().pageTable.size(); i++){
                         int  t = cpuQueue.front().pageTable[i].get_frameNu();
                           cout <<hex<< ( t*pageSize) + g<<"||";} 
                           cout << endl;
                           cout<< endl;         
                       //-----------------------------------------------------
                       double ptmp;
                      cout<< " Please enter current processing time: "<<endl;
                      cout<<">";
                     stringstream strs;
                     string input_ptmp;
                     cin >> input_ptmp;
                     strs << input_ptmp;
                     strs>>ptmp;
                     if (strs.fail()){
                     cout<< "Please enter a number"<<endl;
                     cin >> ptmp;}
                    //  cin>> ptmp;
                     // total_CPU_Times += ptmp;
                      while (ptmp <=0 || ptmp > TimeSlice)
                      {
                          cout<<" Please enter a valid processing time " <<endl;
                          cout<<">";
                          cin>>ptmp;

                      }
                      total_CPU_Times += ptmp;
                      cpuQueue.front().set_pTime(ptmp);
                      cpuQueue.front().set_ProcessBurstTime(cpuQueue.front().get_pTime());
                  cpuQueue.front().set_ProcessBurstCount(1);
                  cpuQueue.front().set_ProcessAvgBurstTime(cpuQueue.front().get_ProcessBurstTime(),cpuQueue.front().get_ProcessBurstCount());
                  AllProcessesBurstTime += cpuQueue.front().get_ProcessBurstTime();
                  CompletedProcesses++;
                  set_SysAvgBurstTime( AllProcessesBurstTime,CompletedProcesses);

                      //----------------------------------------------------------------



                        PRvec[HDN].PRqueue.push(cpuQueue.front());
                        PRvec[HDN].PRqueue.back().setType(" CPU");
                        cpuQueue.pop();
                        CPU_is_free= true;
}
}
}
//----------------------------------Case 4--------------------------------------------------------------------

//-----------------------------------   CASE 4 -----------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
 else if (action == "d0" || action == "d1" || action=="d2" || action=="d3" || action=="d4" || action =="d5"){
      // vector <Process> tempVec;
       int HDN;
       char ignor;
       stringstream ss(action);
       ss>> ignor >> HDN;
       double ptm;
       int CylinderNum;
       if (HDN >= n) {
             cout<< " you have only "<< n << " Hard Drives "<<endl;
             cout<< " NOTE: counting starts at 0 "<<endl;
             }


       else{
           if(CPU_is_free){
                 cout<<" there is no process in CPU to access Hard Disk"<<endl;}
                // throw -1;

           if( !CPU_is_free){
                  cout<< " please enter current processing time: "<<endl;
                  cout<<">";
                    stringstream strd;
                     string input_ptm;
                     cin >> input_ptm;
                     strd << input_ptm;
                     strd>>ptm;
                     if (strd.fail()){
                     cout<< "please enter a number"<<endl;
                     cin >> ptm;}
                //  cin>> ptm;
               //   total_CPU_Times += ptm;
                  while (ptm <=0 || ptm > TimeSlice)
                  {
                      cout<<" please enter a valid processing time " <<endl;
                      cout<<">";
                      cin>>ptm;
                  }
                  total_CPU_Times += ptm;
                  cout<< " please enter cylinder number: "<<endl;
                  cout<<">";
                  

                     stringstream sc;
                     string input_cyl;
                     cin >> input_cyl;
                     sc << input_cyl;
                     sc>>CylinderNum;
                     if (sc.fail()){
                     cout<< "please enter a number"<<endl;
                     cin >> CylinderNum;}
                 // cin>> CylinderNum;

                  while (CylinderNum <=0 || CylinderNum > HDvec[HDN].get_CylinderNUM() )
                  {
                      cout<<" please enter a valid cylinder number " <<endl;
                      cout<<">";
                      cin>>CylinderNum;
                  }
                  char rw;
                  cout << " please enter 'R' for read or 'W' for write"<<endl;
                  cin>> rw;
                  while (rw !='r' && rw !='R' && rw !='w' && rw !='W'){
                        cout<<" invalid selection, try again"<<endl;
                        cin>> rw;
                        }
                   if( rw == 'r' || rw=='R'){
                     //  int startingMem;   // maybe string better to avoid errors
                       string startingMem;
                    //   int length;
                       string length="  ";
                       string file_name;
                       cout<<" please enter starting memory "<<endl;
                       cin >> startingMem;
                     //  cout<< " please enter length "<<endl;
                    //   cin >> length;
                       cout<<" please enter file name "<<endl;
                       cin>> file_name;
                       cpuQueue.front().setMSR(startingMem);   // include them in def
                       cpuQueue.front().setMLR(length);
                       cpuQueue.front().setFileName(file_name);
                       cpuQueue.front().set_WRX(rw);
                       }

                    if (rw == 'w' || rw=='W'){

                       // int startMemoryW;
                        string startMemoryW;
                      //  int fileLong;
                        string fileLong;
                        string fileNm;
                        cout <<" please enter start memeory" <<endl;
                        cin>> startMemoryW;
                        cout<<" How long is the file ?"<<endl;
                        cin>> fileLong;
                        cout<< " Please enter file name "<<endl;
                        cin>> fileNm;
                        cpuQueue.front().setMSR(startMemoryW);   // include them in def
                        cpuQueue.front().setMLR(fileLong);
                        cpuQueue.front().setFileName(fileNm);
                        cpuQueue.front().set_WRX(rw);
                        }
                        //----------------------------------------------------------------------
                              cout<< " Please enter logical address in Hex ! "<<endl;
                       //----------------------------
                              stringstream sshex;
                            // string input_hd;
                          //  cin >> input_hd;
                          //   hd << PHexAdd;
                          //     hd>>n;
                       //---------------------------
                       int hexad;
                       string PHexAdd;
                       cin>> PHexAdd;
                       for (int l =0; l<PHexAdd.size();l++){
                           if ( PHexAdd[l] != '0' && PHexAdd[l] != '1' && PHexAdd[l] != '2' && PHexAdd[l] != '3' && PHexAdd[l] != '4' && PHexAdd[l] != '5' && 
                           PHexAdd[l] != '6' && PHexAdd[l] != '7' && PHexAdd[l] != '8' && PHexAdd[l] != '9' && PHexAdd[l] != 'A' && PHexAdd[l] != 'a' && PHexAdd[l] != 'B'&& 
                           PHexAdd[l] != 'b' && PHexAdd[l] != 'c'&& PHexAdd[l] != 'C' && PHexAdd[l] != 'D' && PHexAdd[l] != 'd' && PHexAdd[l] != 'E' && PHexAdd[l] != 'e'&& 
                           PHexAdd[l] != 'F' && PHexAdd[l] != 'f' ){
                                      cout << " Invalid hex number, try again "<<endl;
                                      cin>>PHexAdd;}}
                        cpuQueue.front().set_logAdd(PHexAdd );              
                        sshex << PHexAdd;               
                      
                    //  stringstream shex;
                        sshex>>  std::hex>> hexad;
                        cpuQueue.front().set_pageNum(hexad);
                        if ( maxPagesPerProc <= cpuQueue.front().get_pageNum()){ // maybe <=
                              cout <<"  INACCESSIBLE ADDRESS ,  !"<<endl;
                              cout << " Please enter a valid hex address" <<endl;
                              cin>>PHexAdd;
                              cpuQueue.front().set_logAdd(PHexAdd );
                              sshex << PHexAdd;
                              sshex>>  std::hex>> hexad;
                              cpuQueue.front().set_pageNum(hexad);
                              }
                      //  cout << "in dec "<<hexad<<endl;  
                       // cpuQueue.front().set_pageNum(hexad);
                     //   cout<<"page number "<< cpuQueue.front().get_pageNum()<<endl;
                        cpuQueue.front().set_pageOffset(hexad);
                    //    cout<<"page offset "<<cpuQueue.front().get_pageOffset()<<endl;
                        cout<<endl; 
                        cout << " Page Table for this process as follow: "<<endl;
                        cout<<"--------FRAMES #----------------"<<endl; 
                        for ( int i =0; i< cpuQueue.front().pageTable.size(); i++){
                            cout<< cpuQueue.front().pageTable[i].get_frameNu();
                            cout<<" || ";
                            }         
                          cout <<endl; 
                         cout<< " Their Physical Addresses Respectively Are :"<<endl;  
                         cout<<"---------------------------------------"<<endl;
                        
                         int g =cpuQueue.front().get_pageOffset();
                         for ( int i =0; i< cpuQueue.front().pageTable.size(); i++){
                         int  t = cpuQueue.front().pageTable[i].get_frameNu();
                           cout <<hex<< ( t*pageSize) + g<<"||";} 
                           cout << endl;
                           cout<< endl; 
                        //----------------------------------------------------------------------
                        cpuQueue.front().set_pTime(ptm);
                        cpuQueue.front().set_CylinderNum(CylinderNum);
                    
                      //  -------------------------
                  cpuQueue.front().set_ProcessBurstTime(cpuQueue.front().get_pTime());
                  cpuQueue.front().set_ProcessBurstCount(1);
                  cpuQueue.front().set_ProcessAvgBurstTime(cpuQueue.front().get_ProcessBurstTime(),cpuQueue.front().get_ProcessBurstCount());
                 AllProcessesBurstTime += cpuQueue.front().get_ProcessBurstTime();
                  //AllProcessesBurstTime += cpuQueue.front().get_pTime();
                  CompletedProcesses++;
                  set_SysAvgBurstTime( AllProcessesBurstTime,CompletedProcesses);
                  //-------------------------//
                        
                        HDvec[HDN].HDvector.push_back(cpuQueue.front());    /// or enqueue it to HD queue then to vrctor , arrange the back to ready queue.
                        //------------------------------------------------------------------------------------------------//
                        if( ! HDvec[HDN].HDqueue.empty() &&  HDvec[HDN].HDqueue.size()>0){
                            while ( HDvec[HDN].HDqueue.size()>0){
                                   HDvec[HDN].HDvector.push_back(HDvec[HDN].HDqueue.front());
                                   HDvec[HDN].HDqueue.pop();
                                   }
                                   }
                            if (  HDvec[HDN].HDvector.size()>1){
                            sort (HDvec[HDN].HDvector.begin(),HDvec[HDN].HDvector.end(),cmp);
                            }

                            for (int i=0; i< HDvec[HDN].HDvector.size(); i++){
                                 if (HDvec[HDN].HDvector[i].get_CylinderNum() >= HDvec[HDN].get_headPosition()){
                                 HDvec[HDN].HDqueue.push(HDvec[HDN].HDvector[i]);}
                                 }


                            for (int i=0; i< HDvec[HDN].HDvector.size(); i++){
                                 if (HDvec[HDN].HDvector[i].get_CylinderNum() < HDvec[HDN].get_headPosition()){
                                 HDvec[HDN].HDqueue.push(HDvec[HDN].HDvector[i]);}
                                 }

                         HDvec[HDN].HDvector.clear();


                       // HDvec[HDN].HDqueue.push(cpuQueue.front());//
                       // HDvec[HDN].HDqueue.back().setType(" CPU");
                        cpuQueue.pop();
                        CPU_is_free= true;
            }
       }
}



//------------------------------------   CASE 5 ---------------------------------------------------------------
 else if (action == "c0" || action == "c1" || action=="c2" || action=="c3" || action=="c4" || action =="c5"){

       int HDN;
       char ignor;
       stringstream ss(action);
       ss>> ignor >> HDN;

       if (HDN >= k) {
             cout<< " you have only "<< k << " CD/RW "<<endl;
             cout<< " NOTE: counting starts at 0 "<<endl;
               //break ;
             }
       else {
                if(CPU_is_free){
                 cout<<" there is no process in CPU to access CD/RW"<<endl;
               //  throw -1;
              //  return;
                 }
                  if( !CPU_is_free){
                  char rw;
                  cout << " please enter 'R' for read or 'W' for write"<<endl;
                  cin>> rw;
                  while (rw !='r' && rw !='R' && rw !='w' && rw !='W'){
                        cout<<" invalid selection, try again"<<endl;
                        cin>> rw;
                        }
                   if( rw == 'r' || rw == 'R'){
                      // int startingMem;   // maybe string better to avoid errors
                       string startingMem ;
                      // int length;
                       string length="   ";
                       string file_name;
                      cout<<" please enter starting memory "<<endl;
                      cin >> startingMem;
                     //  cout<< " please enter length "<<endl;
                     //  cin >> length;
                       cout<<" please enter file name "<<endl;
                       cin>> file_name;
                       cpuQueue.front().setMSR(startingMem);   //
                       cpuQueue.front().setMLR(length);
                       cpuQueue.front().setFileName(file_name);
                       cpuQueue.front().set_WRX(rw);
                       }

                      if  (rw == 'w' || rw=='W'){
                       // int startMemoryW;
                        string startMemoryW;
                       // int fileLong;
                        string fileLong;
                        string fileNm;
                        cout <<" Please enter starting  memeory" <<endl;
                        cin>> startMemoryW;
                        //if ( !isdigit(startMemoryW)){ cout<< "error";}
                        cout<<" How long is the file ?"<<endl;
                        cin>> fileLong;
                        cout<< " Please enter file name "<<endl;
                        cin>> fileNm;
                        cpuQueue.front().setMSR(startMemoryW);   // include them in def
                        cpuQueue.front().setMLR(fileLong);
                        cpuQueue.front().setFileName(fileNm);
                        cpuQueue.front().set_WRX(rw);
                        }
                      //-----------------------------------------------------
                      double ptmc;
                      cout<< " Please enter current processing time: "<<endl;
                      cout<<">";
                     stringstream stc;
                     string input_ptmc;
                     cin >> input_ptmc;
                     stc << input_ptmc;
                     stc>>ptmc;
                     if (stc.fail()){
                     cout<< "Please enter a number"<<endl;
                     cin >> ptmc;}
                     // cin>> ptmc;
                    //  total_CPU_Times +=ptmc;
                      while (ptmc <=0 || ptmc > TimeSlice)
                      {
                          cout<<" Please enter a valid processing time " <<endl;
                          cout<<">";
                          cin>>ptmc;

                      }
                      total_CPU_Times +=ptmc;
                      cpuQueue.front().set_pTime(ptmc);
                       //-------------------------
                  cpuQueue.front().set_ProcessBurstTime(cpuQueue.front().get_pTime());
                  cpuQueue.front().set_ProcessBurstCount(1);
                  cpuQueue.front().set_ProcessAvgBurstTime(cpuQueue.front().get_ProcessBurstTime(),cpuQueue.front().get_ProcessBurstCount());
                  AllProcessesBurstTime += cpuQueue.front().get_ProcessBurstTime();
                  CompletedProcesses++;
                  set_SysAvgBurstTime( AllProcessesBurstTime,CompletedProcesses);
                  //-------------------------
                      
                      //-----------------------------------------------------------------
                         cout<< " please enter logical address in Hex ! "<<endl;
                       //----------------------------
                              stringstream sshex;
                            // string input_hd;
                          //  cin >> input_hd;
                          //   hd << PHexAdd;
                          //     hd>>n;
                       //---------------------------
                       int hexad;
                       string PHexAdd;
                       cin>> PHexAdd;
                       for (int l =0; l<PHexAdd.size();l++){
                           if ( PHexAdd[l] != '0' && PHexAdd[l] != '1' && PHexAdd[l] != '2' && PHexAdd[l] != '3' && PHexAdd[l] != '4' && PHexAdd[l] != '5' && 
                           PHexAdd[l] != '6' && PHexAdd[l] != '7' && PHexAdd[l] != '8' && PHexAdd[l] != '9' && PHexAdd[l] != 'A' && PHexAdd[l] != 'a' && PHexAdd[l] != 'B'&& 
                           PHexAdd[l] != 'b' && PHexAdd[l] != 'c'&& PHexAdd[l] != 'C' && PHexAdd[l] != 'D' && PHexAdd[l] != 'd' && PHexAdd[l] != 'E' && PHexAdd[l] != 'e'&& 
                           PHexAdd[l] != 'F' && PHexAdd[l] != 'f' ){
                                      cout << " invalid hex number, try again "<<endl;
                                      cin>>PHexAdd;}}
                        cpuQueue.front().set_logAdd(PHexAdd );              
                        sshex << PHexAdd;               
                      
                    //  stringstream shex;
                        sshex>>  std::hex>> hexad;
                        cpuQueue.front().set_pageNum(hexad);
                        if ( maxPagesPerProc <= cpuQueue.front().get_pageNum()){ // maybe <=
                              cout <<" INACCESSIBLE ADDRESS !"<<endl;
                              cout << " please enter a valid hex address" <<endl;
                              cin>>PHexAdd;
                              cpuQueue.front().set_logAdd(PHexAdd );
                              sshex << PHexAdd;
                              sshex>>  std::hex>> hexad;
                              cpuQueue.front().set_pageNum(hexad);
                              }
                     //   cout << "in dec "<<hexad<<endl;  
                       // cpuQueue.front().set_pageNum(hexad);
                     //   cout<<"page number "<< cpuQueue.front().get_pageNum()<<endl;
                        cpuQueue.front().set_pageOffset(hexad);
                     //   cout<<"page offset "<<cpuQueue.front().get_pageOffset()<<endl;
                        cout<<endl; 
                        cout << " Page Table for this process as follow: "<<endl;
                        cout<<"--------FRAMES #----------------"<<endl; 
                        for ( int i =0; i< cpuQueue.front().pageTable.size(); i++){
                            cout<< cpuQueue.front().pageTable[i].get_frameNu();
                            cout<<" || ";
                            }         
                          cout <<endl; 
                         cout<< " Their Physical Addresses Respectively Are :"<<endl;  
                         cout<<"---------------------------------------"<<endl;
                        
                         int g =cpuQueue.front().get_pageOffset();
                         for ( int i =0; i< cpuQueue.front().pageTable.size(); i++){
                         int  t = cpuQueue.front().pageTable[i].get_frameNu();
                           cout <<hex<< ( t*pageSize) + g<<"||";} 
                           cout << endl;
                           cout<< endl; 
                      //----------------------------------------------------------------


                        CDvec[HDN].CDqueue.push(cpuQueue.front());//
                        CDvec[HDN].CDqueue.back().setType(" CPU");
                        cpuQueue.pop();
                        CPU_is_free= true;
       }
   }
}
//------------------------------------------ CASE 6 ----------------------------------------------------------------

        else if (action == "D0" || action == "D1" || action=="D2" || action=="D3" || action=="D4" || action =="D5"){

       int HDN;
       char ignor;
       stringstream ss(action);
       ss>> ignor >> HDN;

       if (HDN >= n) {
             cout<< " You have only "<< n << " Hard Drives "<<endl;
             cout<< " NOTE: counting starts at 0 "<<endl;
             }

       else{
                 if(HDvec[HDN].HDqueue.size()==0){
                 cout<<" There is no process in HD " <<HDN<<" queue "<<endl;
               //  throw -1;
                 }
                else if( HDvec[HDN].HDqueue.size()>0){

                     //   if ( HDvec[HDN].HDqueue.size()== 1){
                         /*    HDvec[HDN].set_headPosition(HDvec[HDN].HDqueue.front().get_CylinderNum());
                             cout<<" New head poistion is: " << HDvec[HDN].get_headPosition()<<endl ; //}*/

                        readyQueue.push(HDvec[HDN].HDqueue.front());//
                        readyQueue.back().setType("Hard Drive");
                        // head after cpu pop
                        HDvec[HDN].HDqueue.pop();
                         /*----------------------------------------------------------------------------*/
                        HDvec[HDN].set_headPosition(HDvec[HDN].HDqueue.front().get_CylinderNum());//<-------------------
                        cout<<" New head poistion is: " << HDvec[HDN].get_headPosition()<<endl ; //<------------------------
                        /*----------------------------------------------------------------------*/
                        if( !HDvec[HDN].HDqueue.empty()){
                        cout<<" The front process ID in d queue now is "<< HDvec[HDN].HDqueue.front().getID()<<endl; // NOT NEEDED / DEBUG USE
                        }
                 } // if HD size > 0
       } // if choice = d
}
//---------------------------------------- CASE 7 -----------------------------------------------------------------------------
 else if (action == "P0" || action == "P1" || action=="P2" || action=="P3" || action=="P4" || action =="P5"){

       int HDN;
       char ignor;
       stringstream ss(action);
       ss>> ignor >> HDN;

       if (HDN >= m) {
             cout<< " You have only "<< m << "  Printers "<<endl;
             cout<< " NOTE: counting starts at 0 "<<endl;
              // break ;
             }

       else{
                 if(PRvec[HDN].PRqueue.size()==0){
                 cout<<" There is no process in printer "<< HDN<<"  queue."<<endl;
               //  throw -1;
                 }
                if( PRvec[HDN].PRqueue.size()>0){


                        readyQueue.push(PRvec[HDN].PRqueue.front());
                        readyQueue.back().setType(" Printer");
                        PRvec[HDN].PRqueue.pop();
                        if (PRvec[HDN].PRqueue.size()>0){
                        cout<<" The front process in Printer queue now is "<< PRvec[HDN].PRqueue.front().getID()<<endl; // NOT NEEDED / DEBUG USE
                                }
                 } // if cpu is busy
       } // if choice = d
}
//--------------------------------- CASE 8 ---------------------------------------------------------------
 else if (action == "C0" || action == "C1" || action=="C2" || action=="C3" || action=="C4" || action =="C5"){

       int HDN;
       char ignor;
       stringstream ss(action);
       ss>> ignor >> HDN;

       if (HDN >= k) {
             cout<< " you have only "<< k << " CD/RW "<<endl;
             cout<< " NOTE: counting starts at 0 "<<endl;

             }
       else {

                if(CDvec[HDN].CDqueue.size()==0){
                 cout<<" There is no process in CD/RW "<< HDN<< " queue "<<endl;
               //  throw -1;
                 }
                else if( CDvec[HDN].CDqueue.size()>0){


                        readyQueue.push(CDvec[HDN].CDqueue.front());
                        readyQueue.back().setType(" CD/RW");
                        CDvec[HDN].CDqueue.pop();
                        if ( !CDvec[HDN].CDqueue.empty()){
                        cout<<" The front process in C queue now is "<< CDvec[HDN].CDqueue.front().getID()<<endl; // NOT NEEDED / DEBUG USE
                        }
                 } //
       } //
}
 //------------------------------CASE 9---------------------------------------------------------------------------//
     else if (action == "T"){
          if(CPU_is_free && cpuQueue.empty()){
                 cout<<" there is no process in CPU to Scuedule"<<endl;
                // throw -1;
                 }


                 else if( !CPU_is_free){
                  cpuQueue.front().set_pTime( TimeSlice);
                  cpuQueue.front().setType( "CPU");
                  readyQueue.push(cpuQueue.front()) ;
                  total_CPU_Times += TimeSlice;
                  cpuQueue.pop();
                  CPU_is_free = true;

}
}
//-----------------------------  CASE 10-----------------------------------------------------------
 else if (action[0] == 'K'){
       int specCounter =0;
       int KDN;
       char ignor;
       stringstream kss(action);
       kss>> ignor >> KDN;
       bool found = false;
       // -----1- SEARCH CPU 
       cout <<" Searching for process ID"<< KDN << " ;Please wait "<<endl;
       if(! CPU_is_free && ! found){
              if(cpuQueue.front().getID() == KDN ){
                  cout<< " Found in CPU, system is terminating the process"<<endl;
                  specCounter++;
                  found = true;                        
                  double kptmt;
                  cout<< " Please enter current processing time: "<<endl;
                  cout<<">";
                  stringstream kstrt;
                  string input_kptmt;
                  cin >> input_kptmt;
                  kstrt << input_kptmt;
                  kstrt>>kptmt;
                  if (kstrt.fail()){
                  cout<< "Please enter a number"<<endl;
                  cin >> kptmt;}
                //  cin>> ptmt;
                //  total_CPU_Times += ptmt;
                  while (kptmt <=0 || kptmt > TimeSlice)
                  {
                      cout<<" Please enter a valid processing time " <<endl;
                      cout<<">";
                      cin>>kptmt;

                  }
                  total_CPU_Times += kptmt;

                  cpuQueue.front().set_pTime(kptmt);
                  //-----------------------------------
                  cpuQueue.front().set_ProcessBurstTime(cpuQueue.front().get_pTime());
                  cpuQueue.front().set_ProcessBurstCount(1);
                  cpuQueue.front().set_ProcessAvgBurstTime(cpuQueue.front().get_ProcessBurstTime(),cpuQueue.front().get_ProcessBurstCount());
                  AllProcessesBurstTime += cpuQueue.front().get_ProcessBurstTime();
                  CompletedProcesses++;
                  set_SysAvgBurstTime( AllProcessesBurstTime,CompletedProcesses);
                  //-----------------------------------
                  //-----------------------------------------------------------------------------------------------
                      int kaa = cpuQueue.front().getID(); 
                      
                      for ( int j=0; j< freeFramesV.size() ;j ++){
                        //  cout <<"++++++++++++++"<<endl;
                        //  cout <<freeFramesV[j].get_occupied_by_processId()<<endl;
                          if( freeFramesV[j].get_occupied_by_processId()== kaa){
                              freeFramesV[j].occupied = false;
                              FreeFrames++;
                              FreeMomery = FreeMomery + pageSize;
 
                              cout<<"Frame number : "<<freeFramesV[j].get_frameNu()<<" is now free "<<endl; 
                            //  FreeMomery += pageSize;
                            }
                          //  else { cout<<" skipped"<<endl;}
                            }
                                                                                      
                  
                  
                  //--------------------------------------------------------------------------------------------------
                //  cpuQueue.front().set_avgCPUtime(  cpuQueue.front().get_pTime, cpuQueue.front().get_cpuV);
                 cout<<" The following process has been terminated"<<endl;
                 cout<<" Process ID ||" << setw(12)<< " Total CPU time ||"<< setw(12)<< "Avg. Proc. Time"<<endl;
                 cout<<"---------------------------------------------------------------------------"<<endl;

                 cout<<setw(9)<<cpuQueue.front().getID() <<setw(16)<<cpuQueue.front().get_pTime()<<setw(16) <<cpuQueue.front().get_avgCPUtime()<<endl;
                 cout<<"---------------------------------------------------------------------------"<<endl;
                cout <<"System's  Avg. CPU Time(All Processes)       : " << total_CPU_Times/totalProcesses<<" ms/process"<<endl;
                 cout <<"System Avg Burst Time(Completed Processes) is: " << get_SysAvgBurstTime() <<" ms/completed process"<<endl;
                  cpuQueue.pop();
                  CPU_is_free = true;
                  //-------------------------------------------------------
                  if ( JobPool.size()> 0 ){
                       for ( int j=0; j<JobPool.size(); j++){
                        if ( JobPool[j].get_framesNeeded()<= FreeFrames ){  // you need to make it by frames
                             //----------------------------------------------------
                        int kf =JobPool[j].get_framesNeeded();
                     //   while (f >0){
                        for ( int i =0; i < freeFramesV.size() && kf >0; i++){  
                        if ( freeFramesV[i].occupied == false){
                         freeFramesV[i].set_frameNu(i);    
                         freeFramesV[i].set_occupied_by_processId(JobPool[j].getID());  ////////////////<-------------------    
                         JobPool[j].pageTable.push_back(freeFramesV[i]);
                         kf--;
                      //   freeFramesV[i].set_occupied_by_processId(JobPool[j].getID() ); // MAKE SURE !!!!!!
                         FreeMomery= FreeMomery - pageSize;
                         FreeFrames--;
                         freeFramesV[i].occupied = true;
                        //freeFramesV.erase (freeFramesV.begin()+i);  // it is better to just mark it as in line above
                        }  // an keep fram in vector but with bool marked as occupied
                        }
                      //  }   YOU STILL NEED TO FREE MEMOERY AND FRAMES
                             //----------------------------------------------------
                             readyQueue.push(JobPool[j]);
                           //  FreeFrames= FreeFrames- JobPool[i].get_framesNeeded();
                          //   FreeMomery= FreeMomery -JobPool[j].get_ProcSize();
                             JobPool.erase (JobPool.begin()+j);
                             if ( JobPool.size()> 0 ){
                             std::sort(JobPool.begin(), JobPool.end(), cmp1);}
                             // earse it from vector
                             }
                             }  
                             } 
}
}
// --------2- SEARCH JObPOOL
 if ( JobPool.size() >0 && ! found){
     for ( int i=0; i< JobPool.size() ; i++){
         if ( JobPool[i].getID() == KDN){
               cout<< " Found in JobPool, system is terminating the process"<<endl;
               specCounter ++;
               found = true; 
             JobPool.erase (JobPool.begin()+i); 
             std::sort(JobPool.begin(), JobPool.end(), cmp1);
          //   cout<< " found in job pool and terminated "<<endl;
             }
             }
     
     
}     
//------3- Search readyQueue()
 if ( readyQueue.size()> 0 && ! found){
           backup = readyQueue;  // first search for it if found make two temporary queues 
           int ki=0;       ///   copy queue into another execpt that value if found send it to second one 
           while (backup.size()>0){ // reconstruct ready queue with same order - use function reorder- delete the value 
               if (backup.front().getID()== KDN){ //from second queue
                  cout<< " Found in Ready Queue,system is terminating the process"<<endl;
                  specCounter ++;
                  found = true; 
                  ki++;
                  }
                  backup.pop();
                  } 
                  if ( ki >0){
               //   cout << " found in ready queue" <<endl;     
                  queue < Process> q1,q2;
                  while ( readyQueue.size()>0 )
                  {
                        if (readyQueue.front().getID() != KDN){
                                                       q1.push(readyQueue.front());
                                                       readyQueue.pop();}
                        else if  (readyQueue.front().getID() == KDN){
                                                       q2.push(readyQueue.front());
                                                       readyQueue.pop();}
                  }
                  
                  
                  while ( q1.size()>0 )
                  {
                   readyQueue.push(q1.front());
                   q1.pop();
                  }
                  if (q2.size()>0){
                    int kaar = q2.front().getID(); 
                      
                      for ( int j=0; j< freeFramesV.size() ;j ++){  // lazy delete it from freeframes
                        //  cout <<"++++++++++++++"<<endl;
                        //  cout <<freeFramesV[j].get_occupied_by_processId()<<endl;
                          if( freeFramesV[j].get_occupied_by_processId()== kaar){
                              freeFramesV[j].occupied = false;
                              FreeFrames++;
                              FreeMomery = FreeMomery + pageSize;
                              cout<<"frame number : "<<freeFramesV[j].get_frameNu()<<" is now free "<<endl; 
                            //  FreeMomery += pageSize;
                            }
                          //  else { cout<<" skipped"<<endl;}
                            }
                        
                        q2.pop();
                        }
                        
                   
                   //------------------
                     if ( JobPool.size()> 0 ){
                       for ( int j=0; j<JobPool.size(); j++){
                        if ( JobPool[j].get_framesNeeded()<= FreeFrames ){  // you need to make it by frames
                             //----------------------------------------------------
                        int f =JobPool[j].get_framesNeeded();
                     //   while (f >0){
                        for ( int i =0; i < freeFramesV.size() && f >0; i++){  
                        if ( freeFramesV[i].occupied == false){
                         freeFramesV[i].set_frameNu(i);    
                         freeFramesV[i].set_occupied_by_processId(JobPool[j].getID());  ////////////////<-------------------    
                         JobPool[j].pageTable.push_back(freeFramesV[i]);
                         f--;
                      //   freeFramesV[i].set_occupied_by_processId(JobPool[j].getID() ); // MAKE SURE !!!!!!
                         FreeFrames--;
                         FreeMomery= FreeMomery - pageSize;
                         freeFramesV[i].occupied = true;
                        //freeFramesV.erase (freeFramesV.begin()+i);  // it is better to just mark it as in line above
                        }  // an keep fram in vector but with bool marked as occupied
                        }
                      //  }   YOU STILL NEED TO FREE MEMOERY AND FRAMES
                             //----------------------------------------------------
                             readyQueue.push(JobPool[j]);
                           //  FreeFrames= FreeFrames- JobPool[i].get_framesNeeded();
                          //   FreeMomery= FreeMomery -JobPool[j].get_ProcSize();
                             JobPool.erase (JobPool.begin()+j);
                             if ( JobPool.size()> 0 ){
                             std::sort(JobPool.begin(), JobPool.end(), cmp1);}
                             // earse it from vector
                             }
                             }  
                             } 
                   
                   
                   //------------------
                    } // if found
                 
                                        
}
//-----------4- search in printers queues
 if ( PRvec.size()>0 && !found){
     for ( int t =0; t<PRvec.size(); t++){
         if (PRvec[t].PRqueue.size()>0){
//--------------------------
 backup = PRvec[t].PRqueue;  // first search for it if found make two temporary queues 
           int pi=0;       ///   copy queue into another execpt that value if found send it second one 
           while (backup.size()>0){ // reconstruct ready queue with same order - use function reorder- delete the value 
               if (backup.front().getID()== KDN){ //from second queue
                  cout<< " Found in Printer Queue, system is terminating the process"<<endl;
                  specCounter ++;
                  found = true; 
                  pi++;
                  }
                  backup.pop();
                  } 
                  if ( pi >0){
               //   cout << " found in printer queue" <<endl;     
                  queue < Process> q1,q2;
                  while ( PRvec[t].PRqueue.size()>0 )
                  {
                        if (PRvec[t].PRqueue.front().getID() != KDN){
                                                       q1.push(PRvec[t].PRqueue.front());
                                                       PRvec[t].PRqueue.pop();}
                        else if  (PRvec[t].PRqueue.front().getID() == KDN){
                                                       q2.push(PRvec[t].PRqueue.front());
                                                       PRvec[t].PRqueue.pop();}
                  }
                  
                  
                  while ( q1.size()>0 )
                  {
                   PRvec[t].PRqueue.push(q1.front());
                   q1.pop();
                  }
                  if (q2.size()>0){
                    int paar = q2.front().getID(); 
                      
                      for ( int j=0; j< freeFramesV.size() ;j ++){
                        //  cout <<"++++++++++++++"<<endl;
                        //  cout <<freeFramesV[j].get_occupied_by_processId()<<endl;
                          if( freeFramesV[j].get_occupied_by_processId()== paar){
                              freeFramesV[j].occupied = false;
                              FreeFrames++;
                              FreeMomery = FreeMomery + pageSize;
                              cout<<"Frame Number : "<<freeFramesV[j].get_frameNu()<<" is now free "<<endl; 
                            //  FreeMomery += pageSize;
                            }
                          //  else { cout<<" skipped"<<endl;}
                            }
                        
                        q2.pop();
                        }
                        
                   
                   //------------------
                     if ( JobPool.size()> 0 ){
                       for ( int j=0; j<JobPool.size(); j++){
                        if ( JobPool[j].get_framesNeeded()<= FreeFrames ){  // you need to make it by frames
                             //----------------------------------------------------
                        int f =JobPool[j].get_framesNeeded();
                     //   while (f >0){
                        for ( int i =0; i < freeFramesV.size() && f >0; i++){  
                        if ( freeFramesV[i].occupied == false){
                         freeFramesV[i].set_frameNu(i);
                         freeFramesV[i].set_occupied_by_processId(JobPool[j].getID());  ////////////////<-------------------    
                         JobPool[j].pageTable.push_back(freeFramesV[i]);
                         f--;
                      //   freeFramesV[i].set_occupied_by_processId(JobPool[j].getID() ); // MAKE SURE !!!!!!
                         FreeFrames--;
                         FreeMomery= FreeMomery - pageSize;
                         freeFramesV[i].occupied = true;
                        //freeFramesV.erase (freeFramesV.begin()+i);  // it is better to just mark it as in line above
                        }  // an keep fram in vector but with bool marked as occupied
                        }
                      //  }   YOU STILL NEED TO FREE MEMOERY AND FRAMES
                             //----------------------------------------------------
                             readyQueue.push(JobPool[j]);
                           //  FreeFrames= FreeFrames- JobPool[i].get_framesNeeded();
                            // FreeMomery= FreeMomery -JobPool[j].get_ProcSize();
                             JobPool.erase (JobPool.begin()+j);
                             if ( JobPool.size()> 0 ){
                             std::sort(JobPool.begin(), JobPool.end(), cmp1);}
                             // earse it from vector
                             }
                             }  
                             } 
                   
                   
                   //------------------
                    } // if found
                 
                                        
}                                        
                                        
}
}
//--------------5- SEARCH CD QUEUES
 if ( CDvec.size()>0 && !found ){
     for ( int t =0; t<CDvec.size(); t++){
         if (CDvec[t].CDqueue.size()>0){
//--------------------------
 backup = CDvec[t].CDqueue;  // first search for it if found make two temporary queues 
           int ci=0;       ///   copy queue into another execpt that value if found send it second one 
           while (backup.size()>0){ // reconstruct ready queue with same order - use function reorder- delete the value 
               if (backup.front().getID()== KDN){ //from second queue
                   cout<< " Found in CD Queue, system is terminating the process"<<endl;
                   specCounter ++;
                  found = true; 
                  ci++;
                  }
                  backup.pop();
                  } 
                  if ( ci >0){
               //   cout << " found in CD queue" <<endl;     
                  queue < Process> q1,q2;
                  while ( CDvec[t].CDqueue.size()>0 )
                  {
                        if (CDvec[t].CDqueue.front().getID() != KDN){
                                                       q1.push(CDvec[t].CDqueue.front());
                                                       CDvec[t].CDqueue.pop();}
                        else if  (CDvec[t].CDqueue.front().getID() == KDN){
                                                       q2.push(CDvec[t].CDqueue.front());
                                                       CDvec[t].CDqueue.pop();}
                  }
                  
                  
                  while ( q1.size()>0 )
                  {
                   CDvec[t].CDqueue.push(q1.front());
                   q1.pop();
                  }
                  if (q2.size()>0){
                    int caar = q2.front().getID(); 
                      
                      for ( int j=0; j< freeFramesV.size() ;j ++){
                        //  cout <<"++++++++++++++"<<endl;
                        //  cout <<freeFramesV[j].get_occupied_by_processId()<<endl;
                          if( freeFramesV[j].get_occupied_by_processId()== caar){
                              freeFramesV[j].occupied = false;
                              FreeFrames++;
                              FreeMomery = FreeMomery + pageSize;
                              cout<<"frame number : "<<freeFramesV[j].get_frameNu()<<" is now free "<<endl; 
                            //  FreeMomery += pageSize;
                            }
                          //  else { cout<<" skipped"<<endl;}
                            }
                        
                        q2.pop();
                        }
                        
                   
                   //------------------
                     if ( JobPool.size()> 0 ){
                       for ( int j=0; j<JobPool.size(); j++){
                        if ( JobPool[j].get_framesNeeded()<= FreeFrames ){  // you need to make it by frames
                             //----------------------------------------------------
                        int f =JobPool[j].get_framesNeeded();
                     //   while (f >0){
                        for ( int i =0; i < freeFramesV.size() && f >0; i++){  
                        if ( freeFramesV[i].occupied == false){
                         freeFramesV[i].set_frameNu(i); 
                         freeFramesV[i].set_occupied_by_processId(JobPool[j].getID());  ////////////////<-------------------    
                         JobPool[j].pageTable.push_back(freeFramesV[i]);
                         f--;
                      //   freeFramesV[i].set_occupied_by_processId(JobPool[j].getID() ); // MAKE SURE !!!!!!
                        FreeMomery= FreeMomery -pageSize;
                         FreeFrames--;
                         freeFramesV[i].occupied = true;
                        //freeFramesV.erase (freeFramesV.begin()+i);  // it is better to just mark it as in line above
                        }  // an keep fram in vector but with bool marked as occupied
                        }
                      //  }   YOU STILL NEED TO FREE MEMOERY AND FRAMES
                             //----------------------------------------------------
                             readyQueue.push(JobPool[j]);
                           //  FreeFrames= FreeFrames- JobPool[i].get_framesNeeded();
                           //  FreeMomery= FreeMomery -JobPool[j].get_ProcSize();
                             JobPool.erase (JobPool.begin()+j);
                             if ( JobPool.size()> 0 ){
                             std::sort(JobPool.begin(), JobPool.end(), cmp1);}
                             // earse it from vector
                             }
                             }  
                             } 
                   
                   
                   //------------------
                    } // if found
                 
                                        
}                                        
                                        
}
}
//----------6- SEARCH HD Queues
 if ( HDvec.size()>0 && ! found){
     for ( int i =0; i<HDvec.size(); i++){
         if (HDvec[i].HDqueue.size()>0){
//--------------------------
 backup = HDvec[i].HDqueue;  // first search for it if found make two temporary queues 
           int hi=0;       ///   copy queue into another execpt that value if found send it second one 
           while (backup.size()>0){ // reconstruct ready queue with same order - use function reorder- delete the value 
               if (backup.front().getID()== KDN){ //from second queue
                  cout<< " Found in HD Queue, system is terminating the process"<<endl;
                  specCounter ++;
                  found = true; 
                  hi++;
                  }
                  backup.pop();
                  } 
                  if ( hi >0){
                //  cout << " found in HD queue" <<endl;     
                  queue < Process> q1,q2;
                  while ( HDvec[i].HDqueue.size()>0 )
                  {
                        if (HDvec[i].HDqueue.front().getID() != KDN){
                                                       q1.push(HDvec[i].HDqueue.front());
                                                       HDvec[i].HDqueue.pop();}
                        else if  (HDvec[i].HDqueue.front().getID() == KDN){
                                                       q2.push(HDvec[i].HDqueue.front());
                                                       HDvec[i].HDqueue.pop();}
                  }
                  
                  
                  while ( q1.size()>0 )
                  {
                   HDvec[i].HDqueue.push(q1.front());
                   q1.pop();
                  }
                  if (  HDvec[i].HDvector.size()>1){
                  sort (HDvec[i].HDvector.begin(),HDvec[i].HDvector.end(),cmp);
                  }
                  if (q2.size()>0){
                    int haar = q2.front().getID(); 
                      
                      for ( int j=0; j< freeFramesV.size() ;j ++){
                        //  cout <<"++++++++++++++"<<endl;
                        //  cout <<freeFramesV[j].get_occupied_by_processId()<<endl;
                          if( freeFramesV[j].get_occupied_by_processId()== haar){
                              freeFramesV[j].occupied = false;
                              FreeFrames++;
                              FreeMomery = FreeMomery + pageSize;
                              cout<<"Frame number : "<<freeFramesV[j].get_frameNu()<<" is now free "<<endl; 
                            //  FreeMomery += pageSize;
                            }
                          //  else { cout<<" skipped"<<endl;}
                            }
                        
                        q2.pop();
                        }
                        
                   
                   //------------------
                     if ( JobPool.size()> 0 ){
                       for ( int j=0; j<JobPool.size(); j++){
                        if ( JobPool[j].get_framesNeeded()<= FreeFrames ){  // you need to make it by frames
                             //----------------------------------------------------
                        int f =JobPool[j].get_framesNeeded();
                     //   while (f >0){
                        for ( int i =0; i < freeFramesV.size() && f >0; i++){  
                        if ( freeFramesV[i].occupied == false){
                         freeFramesV[i].set_frameNu(i); 
                         freeFramesV[i].set_occupied_by_processId(JobPool[j].getID());  ////////////////<-------------------    
                         JobPool[j].pageTable.push_back(freeFramesV[i]);
                         f--;
                      //   freeFramesV[i].set_occupied_by_processId(JobPool[j].getID() ); // MAKE SURE !!!!!!
                         FreeFrames--;
                         freeFramesV[i].occupied = true;
                        //freeFramesV.erase (freeFramesV.begin()+i);  // it is better to just mark it as in line above
                        }  // an keep fram in vector but with bool marked as occupied
                        }
                      //  }   YOU STILL NEED TO FREE MEMOERY AND FRAMES
                             //----------------------------------------------------
                             readyQueue.push(JobPool[j]);
                           //  FreeFrames= FreeFrames- JobPool[i].get_framesNeeded();
                             FreeMomery= FreeMomery -JobPool[j].get_ProcSize();
                             JobPool.erase (JobPool.begin()+j);
                             if ( JobPool.size()> 0 ){
                             std::sort(JobPool.begin(), JobPool.end(), cmp1);}
                             // earse it from vector
                             }
                             }  
                             } 
                   
                   
                   //------------------
                    } // if found
                 
                                        
}                                        
                                        
}
}
 if ( specCounter ==0){
     cout<<" Sorry , System Can't Locate it !"<<endl;
     cout<<" Try Again !!"<<endl;
     }

//---------------------------------------------------------------------------------------------------------------

}  // else if K

 //----------------------------- CASE 11--------------------------------------------------------------------------//
     else if (action == "S"){
          char show;
          cout<<" please enter a choice "<<endl;
          cout<< " 'r' to show processes in Ready Queue"<<endl;
          cout<< " 'p' to show processes in Printer Queues"<<endl;
          cout<< " 'd' to show processes in Hard Disk Queues"<<endl;
          cout<< " 'c' to show processes in CD/RW Queues"<<endl;
          cout<< " 'm' to show system memory information "<<endl;
          cout<<" >>";
          cin >> show;
          while ( show != 'r' && show != 'p' && show != 'd' && show != 'c'  && show !='m')
          {
                cout <<" Enter a valid choice , try again "<<endl;
                cout<<" >>" ;
                cin>> show;
                }
           if ( show == 'r'){
                backup = readyQueue;             
                 cout <<" PID   "<<setw(12)<<"|| Coming From  ||"<<setw(12)<<" Processing Time"<<setw(12)<<" ||AVG Proc.Time"<<"||AVG Burst Time"<<endl;
                 cout<<"-------------------------------------------------------"<<endl;
                 while ( backup.size() > 0)
                 {                
                  cout<< backup.front().getID()<<setw(14)<<backup.front().getType()<<setw(16)<<backup.front().get_pTime()<<setw(17)<<backup.front().get_avgCPUtime()<<setw(14)<<backup.front().get_ProcessAvgBurstTime()<<endl;
                 cout<<"* Page Table *"<<endl;
                 cout<<"-------------"<<endl;
                 for ( int i =0; i<backup.front().pageTable.size();i++){
                     cout<< std::dec<<backup.front().pageTable[i].get_frameNu()<<endl;
                     }
                 backup.pop();
                 cout<<"-------------------------------------------------------"<<endl;
                 }
                 cout<<endl;
                 cout <<"-------------------------------------------------------"<<endl;
                 
                 /// you need to add page tables !!
              //   cout<<" -------------------------------------------------------"<<endl;
                 cout <<"System's Avg.CPU Time(All Processses)        : " << total_CPU_Times/totalProcesses<<" ms/process"<<endl;
                 cout<<"--------------------------------------------------------"<<endl;
                 cout <<"System Avg Burst Time(Completed Processes) is: " << get_SysAvgBurstTime() <<" ms/completed process"<<endl;
                 }
            if ( show == 'p'){

                 cout<<"PID "<<setw(5)<<"||R/W"<<setw(10)<<"|| M.Start" <<setw(10)<<"||Length"<<setw(10)<<"||File Name"<<setw(10)<<"||Proc.Time"<<setw(14)<<"||AVG Proc.Time"<<"|| Avg Burst T"<<endl;
                 cout<<"--------------------------------------------------------------------------------"<<endl;
                 for ( int i=0 ; i < m ; i++){
                 backup = PRvec[i].PRqueue;
                 cout<<" Printer"<<i<<":"<<endl;
                 while ( backup.size() > 0)
                 {
                  cout<< backup.front().getID() <<setw(7) <<backup.front().get_WRX()<<setw(10)<< backup.front().getMSR() <<setw(10)<<backup.front().getMLR() <<setw(10)<<backup.front().getFileName()<<setw(10)<<backup.front().get_pTime()<<setw(12)<<backup.front().get_avgCPUtime()<<setw(12)<<backup.front().get_ProcessAvgBurstTime()<<endl;
                 cout<<" Page Table "<<endl;
                 cout<<"-------------"<<endl;
                 for ( int i =0; i<backup.front().pageTable.size();i++){
                 cout<< std::dec<<backup.front().pageTable[i].get_frameNu()<<endl;
                     }
                 backup.pop();
                 }
              /*   while (PRvec[i].PRqueue.size()>0){
                 cout<< PRvec[i].PRqueue.front().getID() <<setw(15) <<PRvec[i].PRqueue.front().get_WRX()<<setw(15)<< PRvec[i].PRqueue.front().getMSR() <<setw(15)<<PRvec[i].PRqueue.front().getMLR() <<setw(15)<<PRvec[i].PRqueue.front().getFileName()<<endl;
                 PRvec[i].PRqueue.pop();
                 }*/
                 cout<<"-------------------------------------------------------------------------------"<<endl;
                 }
                 cout<<endl;
                  cout <<"System's Avg. CPU Time(All Processes)       : " << total_CPU_Times/totalProcesses<<" ms/process"<<endl;
                 cout<<"--------------------------------------------------------------------------"<<endl;
                 cout <<"System Avg Burst Time(Completed Processes)is: " << get_SysAvgBurstTime()<<" ms/completed process" <<endl;
                 }// show==p

             if ( show == 'd'){

                  cout<<"PID"<<setw(7)<<"|R/W"<<setw(9)<<"|M.strat" <<setw(8)<<"|Length"<<setw(8)<<"|F.Name"<<setw(8)<<"|proc.time"<<setw(8)<<"|AVg procT"<<setw(3)<<"||cyl# "<<"|Avg_Burst_Time"<<endl;
                 cout<<"-------------------------------------------------------------------------------"<<endl;
                 for ( int i=0 ; i < n ; i++){
                     backup=HDvec[i].HDqueue;
                     cout<<" Hard Drives "<<i<<":"<<endl;
                     while (backup.size()>0){
                     cout<< backup.front().getID() <<setw(8) <<backup.front().get_WRX()<<setw(8)<< backup.front().getMSR() <<setw(8)<<backup.front().getMLR() <<setw(8)<<backup.front().getFileName()<<setw(8)<<backup.front().get_pTime()<<setw(12)<<backup.front().get_avgCPUtime()<<setw(8)<<backup.front().get_CylinderNum()<<setw(8)<<backup.front().get_ProcessAvgBurstTime()<<endl;
                     cout<<" Page Table "<<endl;
                     cout<<"-------------"<<endl;
                     for ( int i =0; i<backup.front().pageTable.size();i++){
                     cout<< std::dec<<backup.front().pageTable[i].get_frameNu()<<endl;
                     }
                     backup.pop();
                     }
                 cout<<"----------------------------------------------------------------------------"<<endl;
                 }
                 cout <<"System's  Avg. CPU Time(All Processes)       : " << total_CPU_Times/totalProcesses<<" ms/process"<<endl;
                 cout <<"System Avg Burst Time(Completed Processes) is: " << get_SysAvgBurstTime() <<" ms/completed process"<<endl;
                 cout <<"you are currently using CLOOK Scheduling Algorithm"<<endl;
                 }// show==p

               if ( show == 'c'){

                 cout<<"PID"<<setw(8)<<"|R/W"<<setw(12)<<"|M.Start" <<setw(9)<<"|M.Length"<<setw(8)<<"|F.Name"<<setw(10)<<"|Proc.Time"<<setw(10)<<"|AVG Proc.Time"<<"|Avg Burst time"<<endl;
                 cout<<"----------------------------------------------------------------------------"<<endl;
                 for ( int i=0 ; i < k ; i++){
                     backup= CDvec[i].CDqueue;
                 cout<<"CD/RW"<<i<<":"<<endl;
                 while (backup.size()>0){
                cout<< backup.front().getID() <<setw(10) <<backup.front().get_WRX()<<setw(9)<< backup.front().getMSR() <<setw(9)<<backup.front().getMLR() <<setw(9)<<backup.front().getFileName()<<setw(10)<<backup.front().get_pTime()<<setw(10)<<backup.front().get_avgCPUtime()<<setw(10)<<backup.front().get_ProcessAvgBurstTime()<<endl;
                 cout<<" Page Table "<<endl;
                 cout<<"-------------"<<endl;
                 for ( int i =0; i<backup.front().pageTable.size();i++){
                 cout<< backup.front().pageTable[i].get_frameNu()<<endl;
                 }
                 backup.pop();
                 }
                 cout<<"------------------------------------------------------------------------------"<<endl;
                 }
                 cout <<"System's  Avg. CPU Time(All processes)       : " << total_CPU_Times/totalProcesses<<" ms/process"<<endl;
                 cout <<"System Avg Burst Time(Completed processes) is: " << get_SysAvgBurstTime() <<" ms/completed process"<<endl;
                 }// show==p
                 if ( show == 'm'){
                      cout<< " System total Memory "<<setw(12)<<std::dec<<" Free Memory "<<setw(14)<<std::dec<<"Total Frames"<<setw(14)<<std::dec<<" FreeFrames"<<setw(12)<<endl;
                      cout<< TotalMemorySize<<setw(15)<<FreeMomery<<setw(16)<<AllFramesCounts <<setw(14)<<FreeFrames<<endl;
                      cout << "         Frame Tables    "<<endl;
                      cout<<"---------------------------------"<<endl;
                      cout << " frame number " <<setw(14)<<" process ID "<<setw(12)<<" (-1) indicates free frame"<<endl;
                      for ( int i=0; i< freeFramesV.size(); i++){
                     // cout << " frame number " <<setw(12)<<" process ID "<<setw(12)<<"0000 indicates free frame"<<endl;    
                      cout<<std::dec<<freeFramesV[i].get_frameNu()<<setw(18)<<std::dec<<freeFramesV[i].get_occupied_by_processId()<<endl;
                      }
                      } 
                      



} // while S

//*************************AFTER ALL DONE, CHECK IF CPU IS FREE AND READYQUEUE HAS A PROCESS , IF SO , FEED THE CPU ****************//
 if ( readyQueue.size()>0 && !readyQueue.empty() && CPU_is_free && cpuQueue.empty() ){
                             cpuQueue.push(readyQueue.front());
                             cpuQueue.front().setType(" Ready Queue");
                             cpuQueue.front().set_cpuV(1);
                             readyQueue.pop();
                             CPU_is_free = false;

                             }

} // WHILE TRUE
} // RUNNING MODE

////////////////////////////////////// C L A S S   F U N C T I O N S    D E F I N T I O N //////////////////
///////////////////////////////////////////// ** HardDrives Class ** ///////////////////////////////////////
HardDrives::HardDrives(){}

////////////////////////////////////////////////

  HardDrives::HardDrives( int i){
                         HD_ID=i;
                         headPosition=0;
                         CylinderNUM=0;
                    }
 /*------------------------------------------------------------------------*/
 // HardDrives::HardDrives( string k){
                         // name = k;}
/*---------------------------------------------------------------------------*/
void HardDrives::set_CylinderNUM(int i){ CylinderNUM= i;}
/*---------------------------------------------------------------------------*/
int HardDrives::get_CylinderNUM(){ return CylinderNUM;}
/*---------------------------------------------------------------------------*/
 // queue HDqueue;
 int HardDrives::number_of_items_in_Hd_Queue(){
  // return HDqueue.size();
}
/*----------------------------------------------------------------------------*/

bool HardDrives::is_empty()
{
    // if (HDqueue.size() == 0)
            return true;
//     else
            return false;
}
/*-----------------------------------------------------------------------------*/
void HardDrives::print_HDqueue(){
   //  while(!HDqueue.empty())
     {
//                            cout<< HDqueue.front()<<endl;
//                            HDqueue.pop();
     }
}
/*----------------------------------------------------------------------------*/
int HardDrives::getHD_ID(){
    return HD_ID;
}
/*     -----------------------------------------------                        */
HardDrives::~HardDrives(){}
/*------------------------------------------------------------------------*/
string HardDrives::getName(){ return name;}
//-----------------------------------------------------------------------
void HardDrives::set_headPosition(int p){ headPosition = p;}
int  HardDrives::get_headPosition(){ return headPosition;}
//////////////////////////////////////   ** Printers Calss **  //////////////////////////////////////
Printers::Printers() {}
Printers::~Printers(){}
Printers::Printers( int i)  { PR_ID = i ;}
int Printers::number_of_items_in_PR_Queue(){}
bool Printers::is_empty(){}
void Printers::print_PRqueue(){}
int Printers::getPR_ID(){return PR_ID;}
string Printers::getName(){ return name;}
////////////////////////////////////////  ** Frames    **  ///////////////////////////////////
Frames::Frames(){ frameNu=0;
                  occupied = false;
                  occupied_by_processId=-1;}
Frames::Frames(int x){ frameNu = x;
                     occupied = false;
                     occupied_by_processId=-1;} 
Frames::~Frames(){};
//bool Frames::occupied;
void Frames::set_frameNu(int x){ frameNu= x;}
int Frames::get_frameNu(){ return frameNu;}
void Frames::set_occupied_by_processId( int y){ occupied_by_processId = y;}
int Frames::get_occupied_by_processId(){
    if ( occupied == true){
     return occupied_by_processId;}
     else return -1;}
///////////////////////////////////////   ** CD CLASS  **  ////////////////////////////////////
CD::CD() {}
CD::~CD(){}
CD::CD( int i)  { CD_ID = i ;}
int CD::number_of_items_in_CD_Queue(){}
bool CD::is_empty(){}
void CD::print_CDqueue(){}
int CD::getCD_ID(){ return CD_ID;}
string CD::getName(){ return name;}
/////////////////////////////////////    ** Process Class **  ///////////////////////////////////////
//Process::Process(){};
Process::Process(){
                 pTime=0.0;
                 ID=0;
                 cpuV=0;
                 ProcessBurstTime=0.0;
                 ProcessBurstCount=0;
                 ProcessAvgBurstTime=0.00;
                 ProcSize=0;
                 framesNeeded=0;
                 pageNum=0;
                 pageOffset=0;
                   }
Process::~Process(){};
//Process::Process( int i){ ID = i;}
Process::Process( int i){
                  ID = i;
                  pTime=0.0;
                  cpuV=0;
                  ProcessBurstTime=0.0;
                  ProcessBurstCount=0;
                  ProcessAvgBurstTime=0.00;
                  ProcSize=0;
                  framesNeeded=0;
                  pageNum=0;
                  pageOffset=0;
}
void Process::setID(int i){ ID=i;}
int Process::getID(){ return ID;}
void Process::setType( string i){ type= i;}
string Process::getType(){ return type;}
void Process::set_starting_memory(int i) { starting_memory = i;}
int Process::get_starting_memory() { return starting_memory;}
void Process::set_length(int l){ length = l;}
int Process::getlength(){ return length;}
void Process::set_ending_memory() { ending_memory = starting_memory+length ;}
int Process::get_ending_memory() { return ending_memory;}
void Process::set_WRX( char c){ WRX = c;}
char Process::get_WRX() { return WRX;}
void Process::set_current_location(string s) { current_location = s ;}
string Process::get_current_location() { return current_location;}
//void Process::setMSR( int i){MSR=i; }
void Process::setMSR( string i){MSR=i; }
//void Process::setMLR (int l){ MLR=l;}
void Process::setMLR (string l){ MLR=l;}
//int Process::getMSR(){ return MSR;}
string Process::getMSR(){ return MSR;}
//int Process::getMLR() { return MLR;}
string Process::getMLR() { return MLR;}
void Process::setFileName( string s){ fileName = s;}
string Process::getFileName() {return fileName;}
void Process::set_pTime(double s){ pTime +=s;}
double Process::get_pTime(){ return pTime;}
int Process::get_CylinderNum() {return CylNum;}
void Process::set_CylinderNum(int c){CylNum = c;}
void Process::set_cpuV(int a){cpuV += a;}
int Process::get_cpuV(){ return cpuV;}
//void Process::set_avgCPUtime( pTime, cpuV){ avgCPUtime = pTime/cpuV;}
double Process::get_avgCPUtime(){if (cpuV !=0 )return pTime/cpuV;
                                   else return 0;}
void Process::set_ProcSize(int x){ProcSize = x;} 
int Process::get_ProcSize(){ return ProcSize;}
void Process::set_framesNeeded(int x){ framesNeeded = x;}
int Process::get_framesNeeded(){ return framesNeeded;}
void Process::set_logAdd( string s){ logAdd = s;}
string Process::get_logAdd(){ return logAdd;}
void Process::set_pageNum(int x){ pageNum= x/ pageSize;}
int Process::get_pageNum() { return pageNum;}
void Process::set_pageOffset(int x){ pageOffset = x% pageSize;}
int Process::get_pageOffset(){ return pageOffset;}
//---------------------
void Process::set_ProcessBurstTime( double x){  ProcessBurstTime = x;} // gets updated automatically
double Process::get_ProcessBurstTime() {return ProcessBurstTime;}
void Process::set_ProcessBurstCount(int x){ProcessBurstCount +=x;}  // x=1 
int Process::get_ProcessBurstCount(){return ProcessBurstCount;}
void Process::set_ProcessAvgBurstTime( double x , int y){ if (y!=0) ProcessAvgBurstTime= x/y;
                                                        else ProcessAvgBurstTime= 0;}
double Process::get_ProcessAvgBurstTime(){ return ProcessAvgBurstTime;}
