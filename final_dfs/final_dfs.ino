int adj [26][4] = {0,0,0,0,
                   2,6,0,0,
                   1,3,7,0,
                   2,4,8,0,
                   3,5,9,0,
                   4,10,0,0,
                   1,7,11,0,
                   2,6,8,12,
                   3,7,9,13,
                   4,8,10,14,
                   5,9,15,0,
                   6,12,16,0,
                   7,11,13,17,
                   8,12,14,18,
                   9,13,15,19,
                   10,14,20,0,
                   11,17,21,0,
                   12,16,18,22,
                   13,17,19,23,
                   14,18,20,24,
                   15,19,25,0,
                   16,22,0,0,
                   17,21,23,0,
                   18,22,24,0,
                   19,23,25,0,
                   20,24,0,0};

int intruder_found=0;
int cur_dir = 0;
int cur_pos = 0;
int pos_variant =0;
int last_pos_variant;
int source=21, goal=15, key_block_pos;
int intersection = 0;
int node=0;
int turning_flag = 0;
int gripper_flag = 0;
int put_block_flag = 0;
int no=0;
int mode = 1;
int path[25] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int front =0;
int rear = 0;
int l1,l2,ri1,ri2,ml,mm,mr,x,i;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);


 vertex_adjust(12);
//vertex_adjust(6);
vertex_adjust(8);
vertex_adjust(19);
vertex_adjust(20);
	bfs (source, goal);
     printpath (source, goal);
     last_pos_variant = no;     // this variant is needed to find the last position no in path array
     mode = 5;
     cur_pos = source;
x=0;
	do
	{
		x++;
	}while(path[x]!=goal);

	for(i=0;i<=x;i++)
	{
		Serial.print(path[i]);
                Serial.print(">\t");
	}
Serial.print("\n\n");
Serial.print(millis());
}

void loop() {
  // put your main code here, to run repeatedly: 
  
}


struct vertex
{
 int colour;
 int parent;
};
struct vertex v[25];

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

void printpath (int s, int g)      // saving vertex no in the path array
{                                  // the bot will go from source to vertex following this array
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
   case 6: vertex_adjust (10);  break;       // this 8 cases need to change value for matching with vertices
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
