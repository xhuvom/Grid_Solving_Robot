    #include <LiquidCrystal.h>
LiquidCrystal lcd(30, 32, 5, 4, 3, 2);

                                                   ///  ** Usage Instruction ** // 
                                                   
                                                   // Set nodes on "node_arr[]" array
                                                   // call "bfs_set_path(int source,int goal);" function
                                                   // the path will be stored on "arr[]" array based on number automatically
                                                   // and more importantly, the turns will be stored on "path_ch[]" character array automatically 
                                                   // Created,Revised and debugged by [[[ Abu Anas Shuvom  ]]]
                                                    // ********* ALL RIGHTS RESERVED **************
int adj [21][4] = {0,0,0,0,           
                   2,5,0,0,
                   1,3,6,0,
                   2,4,7,0,
                   3,8,0,0,
                   1,6,9,0,
                   2,5,7,10,
                   3,6,8,11,
                   4,7,12,0,
                   5,10,13,0,
                   6,9,11,14,
                   7,10,12,15,
                   8,11,16,0,
                   9,14,17,0,
                   10,13,18,15,
                   11,14,16,19,
			12,15,20,0,
                   13,18,0,0,
                   14,17,19,0,
                   15,18,20,0,
				   16,19,0,0};
                   

int dummy=1;

char path_ch[10];
int arr[10]={0,0,0,0,0,0,0,0,0,0};
int intruder_found=0;
int pos_variant =0;
int last_pos_variant;
int source=4, goal=20, key_block_pos;
int node=0;
int no=0;
int node_arr[6]={6,10,13,17,0,0};
int path[20] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int rear = 0;
int front=0;
int l1,l2,ri1,ri2,ml,mm,mr,p,i;

struct vertex
{
 int colour;
 int parent;
};
struct vertex v[25];


void setup()
{
 lcd.begin(16, 2);
 lcd.clear();
i=0;
do
{
  node_submit(node_arr[i]);
  i++;
}while(node_arr[i]!=0);

bfs_set_path(source,goal);
p=0;
	do
	{
		p++;
	}while(path[p]!=goal);
    
	for(i=0;i<=p;i++)
	{   
		
		arr[i+1]=path[i];

	}
lcd.setCursor(0,0);
	
        for(i=1;i<=p+1;i++)
	{   
         
lcd.setCursor((i-1)*2,0);	 
lcd.print(arr[i]);

         
		
	}


   arr[0]=3;//arr[2];       // only for return trip
                        // for target trip,arr[0] must be known previously

for(i=1;i<=p;i++)
	{   
       
	 
     path_ch[i]=show_path(arr[i-1],arr[i],arr[i+1]);	 	
	}
for(i=1;i<=p;i++)
{
  lcd.setCursor((i-1)*2,1);
  lcd.print(path_ch[i]);
}
	
 
} 

void loop()
{
}


void bfs_set_path(int source,int goal)
{
  	bfs (source, goal);
     printpath (source, goal);
}

void node_submit(int n)
{
  vertex_adjust(matrix_correc(n));
}

void vertex_adjust (int n)   //adjusting vertex array according to found nodes
{
 int i,j,tem;
 for (i=0;i<4;i++)
 {
   tem=adj[n][i];
   for (j=0;j<4;j++)
   {
    if (adj[tem][j]== n)
     {
      adj[tem][j] = 0;
      break;
     }
   }
   adj[n][i] = 0;
 }
}

int matrix_correc(int n)
{
	switch(n)
	{
	case 8: return 5;
	case 7:return 6;
	case 6:return 7;
	case 5:return 8;
	case 16: return 13;
	case 15:return 14;
	case 14:return 15;
	case 13:return 16;
default: return n;
	}
}
void enque (int n)
{
  path[rear] = n;
  rear++;
}

int deque ()
{
  int temp;
  temp = path[front];
  front++;
  return temp;
}

void bfs (int s, int g)        // main bfs function
{
 int i,j,current,u;
 for (i=1;i<=25;i++)
 {
  v[i].colour = 0;
  v[i].parent = 0;
 }
 v[s].colour = 1;
 v[s].parent = 0;
 enque (s);
 while (intruder_found !=1)
 {
  u = deque();
  if (u == g)
  {
   intruder_found = 1;
   break;
  }
  for (j=0;j<4;j++)
  {
   current = adj[u][j];
   if (current != 0)
   {
    if (v[current].colour == 0)
     {
      v[current].colour= 1;
      v[current].parent = u;
      enque (current);
     }
   }
  }
  v[u].colour = 2;
 }
}

void printpath (int s, int g)      
{                                  
  int i,j;
  for (i=g;i!=s;i=v[i].parent)
  {
   no++;
  }
  j= g;
  for (i=no;no>=0;no--)
  {
   path[no]=j;
   j=v[j].parent;
  }
}

void node_adjust()
{
  switch (node)
  {
   case 6: vertex_adjust (10);  break;       
   case 7: vertex_adjust (9);  break;
   case 9: vertex_adjust (7);  break;
   case 10: vertex_adjust (6);  break;
   case 16: vertex_adjust (20);  break;
   case 17: vertex_adjust (19);  break;
   case 19: vertex_adjust (17);  break;
   case 20: vertex_adjust (16);  break;
   default: vertex_adjust (node);
  }
}


char show_path(int prev,int curr,int next)
{
	if(prev==next)
	{
		return 'U';
	}
	if(abs((curr-prev))==abs((curr-next)))
	{
		return 'F';
	}
	else if((curr-prev)==curr)
	{
		return 'F';
	}
	else if(abs((curr-prev))==abs((curr-next)))
	{
		return 'F';
	}
 
    else if((curr-prev)*(curr-next)*dummy<0)
	{
      dummy=-dummy;
	  return 'L';
	}

	else if((curr-prev)*(curr-next)*dummy>0)
	{

        dummy=-dummy;
		return 'R';
}
	
	else
	{
		return '?';
	}

}





