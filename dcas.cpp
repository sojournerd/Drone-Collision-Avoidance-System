/*
CODE WRITTEN BY IMAN HAKIM-ABDUL-RASHED
Email: ihabdulr@buffalo.edu

Hope you enjoy ;) its pretty cool.

*/

#include <iostream>
#include <thread>
#include <pthread.h>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <mutex>


const int ROW = 20;
const int COL = 20;

std::mutex mtx[ROW][COL];
std::string world[ROW][COL];



class Drone {  //class to hold drone objects..didn't use but kept because I don't enjoy wasting time :3
  std::string str;
  int currentXpos, currentYpos, desXpos, desYpos;
public:
    void set_values(std::string str,int,int,int,int);
};

void Drone::set_values(std:: string str_rep, int cx, int cy, int dx, int dy){
   str = str_rep;
   currentXpos = cx;
   currentYpos = cy;
   desXpos = dx;
   desYpos = dy;
}


void populateWorld(){
//initialize map
 for (int i =0; i< ROW; i++){
   for (int j=0; j<COL; j++){
      world[i][j] = "[  *  ]" ;
      std::cout << world[i][j];
      mtx[i][j].unlock();
   }
   std::cout << std::endl;
 }
}

void updateWorld(int amt){
//function to print the current world to track movements of drones
std::this_thread::sleep_for(std::chrono::seconds(1));

do{

 for (int i =0; i< ROW; i++){

   for (int j=0; j<COL; j++){
      std::cout << world[i][j];
   }
   std::cout << std::endl;
 }
 system("clear");
 amt--;
 } while (amt > 0);
}
//just a stub didn't up using.
void avoid_Collision(){}

void move( std::string ID, int sX, int sY, int destination_X, int destination_Y){
/*Method to have drones move*/

	world[sX][sY] = "[ " + ID + " ]"; //initialize drone at its respective airport
  std::this_thread::sleep_for(std::chrono::seconds(5)); //allow time to see air port
  mtx[sX][sY].lock();
  int startX = sX;
  int startY = sY;
 //loop to execute while drone has not reached its destination
  while(startX != destination_X || startY != destination_Y){
   if (startX < destination_X){
   		while(startX != destination_X){
        if(mtx[startX+1][startY].try_lock()){ //check if drone can move
   			world[startX++][startY] = "[  *  ]";
   			world[startX][startY] = "[ " + ID + " ]";
        mtx[startX-1][startY].unlock();
   			std::this_thread::sleep_for(std::chrono::seconds(1));
      }
      else{  //if drone cant move manuever
        if(mtx[startX][startY+1].try_lock()){
   			world[startX][startY++] = "[  *  ]";
   			world[startX][startY] = "[ " + ID + " ]";
        mtx[startX][startY-1].unlock();
   			std::this_thread::sleep_for(std::chrono::seconds(1));
      }
      }
   		}
   }
   if (startX > destination_X){
   		while(startX != destination_X){
        if(mtx[startX-1][startY].try_lock()){
   			world[startX--][startY] = "[  *  ]";
   			world[startX][startY] = "[ " + ID + " ]";
        mtx[startX+1][startY].unlock();
   			std::this_thread::sleep_for(std::chrono::seconds(1));
      }
      else{
        if(mtx[startX][startY-1].try_lock()){
   			world[startX][startY--] = "[  *  ]";
   			world[startX][startY] = "[ " + ID + " ]";
        mtx[startX][startY+1].unlock();
   			std::this_thread::sleep_for(std::chrono::seconds(1));
      }
      }
   		}

   }
   if (startY < destination_Y){
   		while(startY != destination_Y){
        if(mtx[startX][startY+1].try_lock()){
   			world[startX][startY++] = "[  *  ]";
   			world[startX][startY] = "[ " + ID + " ]";
        mtx[startX][startY-1].unlock();
   			std::this_thread::sleep_for(std::chrono::seconds(1));
      }
      else{
        if(mtx[startX+1][startY].try_lock()){
   			world[startX++][startY] = "[  *  ]";
   			//startX+=1;
   			world[startX][startY] = "[ " + ID + " ]";
        mtx[startX-1][startY].unlock();
   			std::this_thread::sleep_for(std::chrono::seconds(1));
      }
      }
   		}
   }
   if (startY > destination_Y){
   		while(startY != destination_Y){
        if(mtx[startX][startY-1].try_lock()){
   			world[startX][startY--] = "[  *  ]";
   			world[startX][startY] = "[ " + ID + " ]";
        mtx[startX][startY+1].unlock();
   			std::this_thread::sleep_for(std::chrono::seconds(1));
      }
      else{
        if(mtx[startX-1][startY].try_lock()){
   			world[startX--][startY] = "[  *  ]";
   			world[startX][startY] = "[ " + ID + " ]";
        mtx[startX+1][startY].unlock();
   			std::this_thread::sleep_for(std::chrono::seconds(1));
      }
      }
   		}
   }
}
//loop to get the drone back to its airport after completing its tasks
//set 1 second delay so that change can be reflected on printWorld function
while(startX != sX || startY != sY){

  if (startX < sX){
     while(startX != sX){
       if(mtx[startX+1][startY].try_lock()){
       world[startX++][startY] = "[  *  ]";
       world[startX][startY] = "[ " + ID + " ]";
       mtx[startX-1][startY].unlock();
       std::this_thread::sleep_for(std::chrono::seconds(1));
     }
     else{
       if(mtx[startX][startY+1].try_lock()){
       world[startX][startY++] = "[  *  ]";
       world[startX][startY] = "[ " + ID + " ]";
       mtx[startX][startY-1].unlock();
       std::this_thread::sleep_for(std::chrono::seconds(1));
     }
     }
     }
  }
  if (startX > sX){
     while(startX != sX){
       if(mtx[startX-1][startY].try_lock()){
       world[startX--][startY] = "[  *  ]";
       world[startX][startY] = "[ " + ID + " ]";
       mtx[startX+1][startY].unlock();
       std::this_thread::sleep_for(std::chrono::seconds(1));
     }
     else{
       if(mtx[startX][startY-1].try_lock()){
       world[startX][startY--] = "[  *  ]";
       world[startX][startY] = "[ " + ID + " ]";
       mtx[startX][startY+1].unlock();
       std::this_thread::sleep_for(std::chrono::seconds(1));
     }
     }
     }

  }
  if (startY < sY){
     while(startY != sY){
       if(mtx[startX][startY+1].try_lock()){
       world[startX][startY++] = "[  *  ]";
       world[startX][startY] = "[ " + ID + " ]";
       mtx[startX][startY-1].unlock();
       std::this_thread::sleep_for(std::chrono::seconds(1));
     }
     else{
       if(mtx[startX+1][startY].try_lock()){
       world[startX++][startY] = "[  *  ]";
       world[startX][startY] = "[ " + ID + " ]";
       mtx[startX-1][startY].unlock();
       std::this_thread::sleep_for(std::chrono::seconds(1));
     }
     }
     }
  }
  if (startY > sY){
     while(startY != sY){
       if(mtx[startX][startY-1].try_lock()){
       world[startX][startY--] = "[  *  ]";
       world[startX][startY] = "[ " + ID + " ]";
       mtx[startX][startY+1].unlock();
       std::this_thread::sleep_for(std::chrono::seconds(1));
     }
     else{
       if(mtx[startX-1][startY].try_lock()){
       world[startX--][startY] = "[  *  ]";
       world[startX][startY] = "[ " + ID + " ]";
       mtx[startX+1][startY].unlock();
       std::this_thread::sleep_for(std::chrono::seconds(1));
     }
     }
     }
  }



}

}




int main(int argc, char* argv[]){
   /*Fetching the command line arguements */
    // Feteching the airport location for each drone and its destination
    int X_drone1 = atoi(argv[1]), Y_drone1= atoi(argv[2]), X_drone2= atoi(argv[3]), Y_drone2= atoi(argv[4]);
    int destination_X1= atoi(argv[5]), destination_Y1= atoi(argv[6]),destination_X2= atoi(argv[7]), destination_Y2= atoi(argv[8]);

    int X_drone3 = atoi(argv[9]), Y_drone3= atoi(argv[10]), X_drone4= atoi(argv[11]), Y_drone4= atoi(argv[12]);
    int destination_X3= atoi(argv[13]), destination_Y3= atoi(argv[14]),destination_X4= atoi(argv[15]), destination_Y4= atoi(argv[16]);

    int X_drone5 = atoi(argv[17]), Y_drone5= atoi(argv[18]), X_drone6= atoi(argv[19]), Y_drone6= atoi(argv[20]);
    int destination_X5= atoi(argv[21]), destination_Y5= atoi(argv[22]),destination_X6= atoi(argv[23]), destination_Y6= atoi(argv[24]);

    int X_drone7 = atoi(argv[25]), Y_drone7= atoi(argv[26]), X_drone8= atoi(argv[27]), Y_drone8= atoi(argv[28]);
    int destination_X7= atoi(argv[29]), destination_Y7= atoi(argv[30]),destination_X8= atoi(argv[31]), destination_Y8= atoi(argv[32]);

    int X_drone9 = atoi(argv[33]), Y_drone9 = atoi(argv[34]), destination_X9 = atoi(argv[35]), destination_Y9 = atoi(argv[36]);
    //the IDS of each drone in the world
    std::string ID1 = "<1>", ID2 = "<2>" , ID3 = "<3>", ID4 = "<4>", ID5 = "<5>", ID6 = "<6>", ID7 = "<7>", ID8 = "<8>", ID9 = "<9>";


	  populateWorld(); //initialize world

    //initialize drone threads!
    std::thread printThread(updateWorld, 50000);
    std::thread movement1(move, ID1, X_drone1, Y_drone1, destination_X1, destination_Y1);
    std::thread movement2(move, ID2, X_drone2, Y_drone2, destination_X2, destination_Y2);
    std::thread movement3(move, ID3, X_drone3, Y_drone3, destination_X3, destination_Y3);
    std::thread movement4(move, ID4, X_drone4, Y_drone4, destination_X4, destination_Y4);
    std::thread movement5(move, ID5, X_drone5, Y_drone5, destination_X5, destination_Y5);
    std::thread movement6(move, ID6, X_drone6, Y_drone6, destination_X6, destination_Y6);
    std::thread movement7(move, ID7, X_drone7, Y_drone7, destination_X7, destination_Y7);
    std::thread movement8(move, ID8, X_drone8, Y_drone8, destination_X8, destination_Y8);
    std::thread movement9(move, ID9, X_drone9, Y_drone9, destination_X9, destination_Y9);

    //bring each thread to concurrency.
    printThread.join();
    movement1.join();
    movement2.join();
    movement3.join();
    movement4.join();
    movement5.join();
    movement6.join();
    movement7.join();
    movement8.join();
    movement9.join();

return 0;
}
