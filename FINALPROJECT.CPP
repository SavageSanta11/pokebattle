#include<ctype.h>
#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<dos.h>
#include<stdio.h>

class player{
int score;
public:
char playername[30];
int getscore()
	{
	return score;
	}
void putscore(int sc)
	{
	score=sc;
	}
};
class move{
char mname1[20];
char mname2[20];
char mname3[20];
char mname4[20];
public:
void putmname1(char name[])
	{
	strcpy(mname1,name);
	}
void putmname2(char name[])
	{
	strcpy(mname2,name);

	}
void putmname3(char name[])
	{
	strcpy(mname3,name);
	}
void putmname4(char name[])
	{
	strcpy(mname4,name);
	}
void printmname1()
	{
	cout<<mname1;
	}
void printmname2()
	{
	cout<<mname2;
	}
void printmname3()
	{
	cout<<mname3;
	}
void printmname4()
	{
	cout<<mname4;
	}

int dmg1, dmg2, dmg3, dmg4;

//default ctr
move()
	{
	strcpy(mname1,"Default");
	dmg1=0;
	strcpy(mname2,"Default");
	dmg2=0;
	strcpy(mname3,"Default");
	dmg3=0;
	strcpy(mname4,"Default");
	dmg4=0;
	}
//ctr
move(char m1[20],int d1,char m2[20],int d2,char m3[20],int d3,char m4[20],int d4)
	{
	strcpy(mname1,m1);
	dmg1 = d1;
	strcpy(mname2,m2);
	dmg2 = d2;
	strcpy(mname3,m3);
	dmg3 = d3;
	strcpy(mname4,m4);
	dmg4 = d4;
	}
};

class pokemon{
char name[20];
int id;
int cost;
public:
void printname()
	{
	cout<<name;
	}
int getid()
	{
	return id;
	}
int getcost()
	{
	return cost;
	}
int health;
char type[20];
move pmove;

//default constructor
pokemon()
	{
	id=0;
	cost=0;
	strcpy(name,"Default");
	health=0;
	strcpy(type,"Def");
	}
//ctr
pokemon(int ide,char name1[10],int health1,char type1[10],char m1[10],int d1,char m2[10],int d2,char m3[10],int d3,char m4[10],int d4,int cst) : pmove(m1,d1,m2,d2,m3,d3,m4,d4)
	{
	id=ide;
	cost=cst;
	strcpy(name,name1);
	health=health1;
	strcpy(type,type1);
	pmove.putmname1(m1);
	pmove.dmg1=d1;
	pmove.putmname2(m2);
	pmove.dmg2=d2;
	pmove.putmname3(m3);
	pmove.dmg3=d3;
	pmove.putmname4(m4);
	pmove.dmg4=d4;
	}
void input()
	{
	cout<<"Enter new name: ";
	gets(name);
	cout<<"Enter new type: ";
	gets(type);
	cout<<"Enter new cost: ";
	cin>>cost;
	cout<<"Enter new moves: ";
	char c1[20]; char c2[20]; char c3[20]; char c4[20];
	cin>>c1>>c2>>c3>>c4;
	pmove.putmname1(c1);
	pmove.putmname2(c2);
	pmove.putmname3(c3);
	pmove.putmname4(c4);
	cout<<"Enter new damages: ";
	cin>>pmove.dmg1>>pmove.dmg2>>pmove.dmg3>>pmove.dmg4;
	}
void display()
	{
	cout<<"Pokemon id: "<<id<<'\n';
	cout<<"Pokemon name: "<<name<<'\n';
	cout<<"Pokemon type: "<<type<<'\n';
	cout<<"Cost: "<<cost<<" coins"<<'\n';
	}
void displaymoves()
	{
	cout<<'\t'<<'\t';
	cout<<"1.";pmove.printmname1(); cout<<"("<<pmove.dmg1<<")"<<'\t';
	cout<<"2.";pmove.printmname2(); cout<<"("<<pmove.dmg2<<")"<<'\n';
	cout<<'\t'<<'\t';
	cout<<"3.";pmove.printmname3(); cout<<"("<<pmove.dmg3<<")"<<'\t';
	cout<<"4.";pmove.printmname4(); cout<<"("<<pmove.dmg4<<")"<<'\n';
	cout << '\n';
	cout << "Exit battle(y-0)"<<'\n';
	cout << '\n';
	cout << '\n';
	}
};

void deletepok()
{
int ide;
cout<<"Enter pokemon ID to be deleted: ";
cin>>ide;
int check=0;
pokemon ob;
ifstream fw1;
ofstream fw2;
fw1.open("pro.dat",ios::in|ios::binary);
fw2.open("newpro.dat",ios::out|ios::binary);
while(fw1.read((char*)&ob,sizeof(pokemon)))
	{
	if(ob.getid()==ide)
		{
		cout<<"Pokemon ";
		ob.printname();
		cout<<" deleted. "<<'\n';
		check=1;
		}
	else
		{
		fw2.write((char*)&ob,sizeof(pokemon));
		}
	}
fw1.close();
fw2.close();
if(check==0)
	{
	cout<<"This pokemon not found. "<<'\n';
	}
else
	{
	remove("pro.dat");
	rename("newpro.dat","pro.dat");
	}

}
void leaderboard()
{
int i=0;
player ob;
player arr[20];
ifstream fw;
fw.open("players.dat",ios::in|ios::binary);
while(fw)                            //writing the objects to array
	{
	fw.read((char*)&ob,sizeof(player));
	arr[i]=ob;
	i++;
	}
fw.close();
i--;
for(int k=0;k<i;k++)         //sorting the objects in array
	{
	for (int j=0;j<i-1;j++)
		{
		if (arr[j].getscore()<arr[j+1].getscore())
			{
			player temp;
			temp=arr[j];
			arr[j]=arr[j+1];
			arr[j+1]=temp;
			}
		}
	}
cout<<"LEADERBOARD:"<<'\n'<<"Player name:"<<'\t'<<'\t'<<"Player score:"<<'\n';
for (k=0;k<i;k++)
	{
	cout<<k+1<<". "<<arr[k].playername<<'\t'<<'\t'<<arr[k].getscore()<<'\n';
	}
}
void modify()
{
pokemon s;
fstream file;
file.open("pro.dat",ios::in|ios::binary|ios::out);
int pos=-1;
int in;
cout<<"Enter the pokemon ID to be modified: "<<'\n';
cin>>in;
file.read((char *)&s,sizeof(s));
while(file) {
	if (in==s.getid())
		{
		cout<<"Pokemon is "<<'\n';
		s.display();
		pos=file.tellg()-sizeof(s);
		break;
		}
	file.read((char*)&s,sizeof(s));
	}
if(pos>-1)
	{
	cout<< "Enter new details of the pokemon: "<<'\n';
	s.input();
	file.seekp(pos,ios::beg);
	file.write((char*)&s,sizeof(s));
	cout<< "Pokemon modified successfully. "<<'\n';
	}
else
	{
	cout<< "Pokemon with this id not found. "<<'\n';
	}
file.close();
}



int extra(char s[20],char t[20]){
int dam=0;
if(!strcmp(s,"Flying") && !strcmp(t,"Grass/Poison")){
dam = 20;
}
else if(!strcmp(s,"Electric") && (!strcmp(t,"Flying") || !strcmp(t,"Water"))){
dam = 20;
}
else if(!strcmp(s,"Fire	") && !strcmp(t,"Grass/Poison")){
dam = 20;
}
else if(!strcmp(s,"Grass") && !strcmp(t,"Water	")){
dam = 20;
}
else if(!strcmp(s,"Poison") && !strcmp(t,"Fairy")){
dam = 20;
}
else if(!strcmp(s,"Ground") && (!strcmp(t,"Fire") || !strcmp(t,"Flying	"))){
	dam = 20;
}
else if(!strcmp(s,"Fairy") && (!strcmp(t,"Fighting") || !strcmp(t,"Dragon"))){
dam = 20;

}

else if(!strcmp(s,"Psychic") && (!strcmp(t,"Fighting") || !strcmp(t,"Poison"))){
dam = 20;
}

else if(!strcmp(s,"Grass/Bug") && !strcmp(t,"Psychic")){
dam = 20;
}
else {
dam=0;
}
return dam;
}
void initialise(){
	pokemon obj1 (1,"Pichu",318," ele","Kick",50,"Punch",50,"Slap",50,"Dab",10,100);
	pokemon obj2 (2,"Bulbasaur",318,"Grass/Poison","Power Whip",50,"Seed Bomb",50,"Tackle",60, "Vine Whip",70,75);
	pokemon obj3 (3,"Ivysaur",405,"Grass/Poison","Power Whip",60,"Sludge Bomb",60,"Razor Leaf",70, "Vine Whip",80,150);
	pokemon obj4 (4,"Charmander",309,"Fire","Scratch",50,"Ember",50,"Flame Burst",60, "Flame Charge",70,75);
	pokemon obj5 (5,"Charmeleon",405,"Fire","Ember",60,"Flame Burst",60, "Flame Charge",70,"Flamethrower",80,150);
	pokemon obj6 (6,"Charizard",534,"Fire","Dragon Claw",70,"Wing Attack",70, "Flame Charge",80,"Flamethrower",90,225);
	pokemon obj7 (7,"Squirtle",314,"Water","Bubble",50,"Aqua Jet",50, "Aqua Tail",60,"Water Pulse",70,75);
	pokemon obj8 (8,"Wartotle",405,"Water","Water Gun",60,"Hydro Pump",60, "Ice Beam",70,"Water Pulse",80,150);
	pokemon obj9 (9,"Blastoise",530,"Water","Water Gun",70,"Flash Cannon",70, "Ice Beam",80,"Hydro Pump",90,225);
	pokemon obj10 (10,"Pidgey",251,"Flying","Tackle",50,"Quick Attack",50, "Aerial Ace",60,"Ace Cutter",70,75);
	pokemon obj11 (11,"Pidgeotto",349,"Flying","Steel Wing",60,"Wing Attack",60, "Aerial Ace",70,"Ace Cutter",80,150);
	pokemon obj12 (12,"Pidgeot",479,"Flying","Steel Wing",70,"Wing Attack",70, "Hurricane",80,"Ace Cutter",90,225);
	pokemon obj13 (13,"Rattata",253,"Normal","Tackle",50,"Quick Attack",50, "Hyper Fang",60,"Body Slam",70,75);
	pokemon obj14 (14,"Raticate",413,"Normal","Bite",60,"Hyper Beam",70, "Hyper Fang",70,"Body Slam",80,150);
	pokemon obj15 (15,"Ekans",288,"Poison","Acid",50,"Poison Sting",50, "Gunk Shot ",60,"Sludge Bomb",70,75);
	pokemon obj16 (16,"Arbok",448,"Poison","Poison Sting",60, "Gunk Shot ",60,"Sludge Wave",70,"Dark Pulse",80,150);
	pokemon obj17 (17,"Pikachu",430,"Electric","Thunder Shock",70, "Quick Attack ",70,"Thunderbolt",70,"Thunder",80,150);
	pokemon obj18 (18,"Raichu",485,"Electric","Thunder Shock",70, "Brick Break ",70,"Thunder Punch",80,"Thunder",90,225);
	pokemon obj19 (19,"Sandshrew",300,"Ground","Scratch",50, "Mud Show ",60,"Rock Slide",60,"Rock Tomb",70,75);
	pokemon obj20 (20,"Sandslash",450,"Ground","Metal Claw",60, "Rock Tomb ",70,"Bulldoze",70,"Earthquake",80,150);
	pokemon obj21 (21,"Nidoran",275,"Poison","Posion Sting",50, "Poison Fang ",50,"Sludge Bomb",60,"Body Slam",70,75);
	pokemon obj22 (22,"Nidoqueen",505,"Poison","Posion Jab",70, "Stone Edge ",80,"Sludge Wave",80,"Earthquake",90,225);
	pokemon obj23 (23,"Nidorino",365,"Poison","Posion Jab",60, "Bite ",60,"Sludge Bomb",70,"Horn Attack",80,150);
	pokemon obj24 (24,"Nidoking",505,"Poison","Posion Jab",70, "Fury Cutter",80,"Megahorn",80,"Earthquake",90,225);
	pokemon obj25 (25,"Clefairy",323,"Fairy","Zen Headbutt",60, "Pound ",60,"Body Slam",70,"Disarming Voice",80,75);
	pokemon obj26 (26,"Clefable",483,"Fairy","Zen Headbutt",70, "Pound ",70,"Psychic",80,"Dazzling Gleam",90,150);
	pokemon obj27 (27,"Vulpix",299,"Fire","Quick Attack",50, "Heat Wave ",50,"Fire Blast",60,"Flamethrower",70,75);
	pokemon obj28 (28,"Ninetales",505,"Fire","Feint Attack",70, "Heat Wave ",80,"Fire Blast",80,"Flamethrower",90,225);
	pokemon obj29 (29,"Paras",285,"Grass/Bug","Bug Bite",50, "Fury Cutter ",60,"Seed Bomb",60,"X-Scissor",70,75);
	pokemon obj30 (30,"Parasect",405,"Grass/Bug","Wing Attack",60, "Fury Cutter ",60,"Solar Beam",70,"Cross Poison",80,150);
	pokemon obj31 (31,"Venonat",305,"Grass/Bug","Confusion",60, "Bug Bite",60,"Signal Beam",70,"Poison Fang",80,75);
	pokemon obj32 (32,"Venomoth",450,"Grass/Bug","Confusion",70, "Bug Bite",70,"Bug Buzz",70,"Psychic",80,150);
	pokemon obj33 (33,"Diglett",265,"Ground","Mud Shot",50, "Rock Tomb",50,"Scratch",60,"Mud Bomb",70,75);
	pokemon obj34 (34,"Dugtrio",425,"Ground","Sucker Punch",60, "Stone Edge",70,"Earthquake",70,"Mud Bomb",80,150);
	pokemon obj35 (35,"Meowth",290,"Normal","Scratch",50, "Dark Pulse",50,"Night Slash",60,"Body Slam",70,75);
	pokemon obj36 (36,"Persian",440,"Normal","Feint Attack",70, "Play Rough",70,"Night Slash",80,"Power Gem",90,150);
	pokemon obj37 (37,"Mankey",305,"Fighting","Scratch",60, "Karate Chop",60,"Brick Break",70,"Cross Chop",80,75);
	pokemon obj38 (38,"Primeape",455,"Fighting","Low Kick",70, "Karate Chop",70,"Night Slash",80,"Cross Chop",90,150);
	pokemon obj39 (39,"Abra",310,"Psychic","Zen Headbutt",60, "Shadow Ball",60,"Signal Beam",60,"Psyshock",70,75);
	pokemon obj40 (40,"Kadabra",400,"Psychic","Confusion",70, "Shadow Ball",70,"Dazzling Gleam",70,"Psybeam",80,150);
	pokemon obj41 (41,"Alakazam",500,"Psychic","Confusion",70, "Psycho cut",80,"Dazzling Gleam",80,"Psychic",90,225);
	pokemon obj42 (42,"Machop",305,"Fighting","Low Kick",60, "Karate Chop",60,"Brick Break",70,"Low Sweep",80,75);
	pokemon obj43 (43,"Machoke",405,"Fighting","Low Kick",70, "Karate Chop",70,"Brick Break",70,"Submission",80,150);
	pokemon obj44 (44,"Machamp",505,"Fighting","Bullet Punch",70, "Karate Chop",80,"Stone Edge",80,"Low Submission",90,225);
	pokemon obj45 (45,"Dratini",300,"Dragon","Dragon Breath",60, "Aqua Tail",60,"Twister",60,"Wrap",70,75);
	pokemon obj46 (46,"Dragonair",420,"Dragon","Dragon Breath",60, "Aqua Tail",70,"Dragon Pulse",70,"Wrap",80,150);
	pokemon obj47 (47,"Dragonite",600,"Dragon","Dragon Breath",70, "Dragon Claw",80,"Dragon Pulse",80,"Hyper Beam",90,225);
	pokemon obj48 (48,"Elekid",360,"Electric","Thunder Shock",60, "Thunder Punch",70,"Brick Break",70,"Discharge",80,150);
	pokemon obj49 (49,"Electabuzz",490,"Electric","Thunder Shock",70, "Thunder Punch",80,"Thunder Bolt",80,"Thunder",90,225);
	pokemon obj50 (50,"Kingdra",540,"Dragon","Water Gun",80, "Dragon Breath",80,"Outrage",80,"Blizzard",90,225);

	fstream fw;
	fw.open("pro.dat",ios::out|ios::binary);
	fw.write((char*)&obj1,sizeof(obj1));
	fw.write((char*)&obj2,sizeof(obj2));
	fw.write((char*)&obj3,sizeof(obj3));
	fw.write((char*)&obj4,sizeof(obj4));
	fw.write((char*)&obj5,sizeof(obj5));
	fw.write((char*)&obj6,sizeof(obj6));
	fw.write((char*)&obj7,sizeof(obj7));
	fw.write((char*)&obj8,sizeof(obj8));
	fw.write((char*)&obj9,sizeof(obj9));
	fw.write((char*)&obj10,sizeof(obj10));
	fw.write((char*)&obj11,sizeof(obj11));
	fw.write((char*)&obj12,sizeof(obj12));
	fw.write((char*)&obj13,sizeof(obj13));
	fw.write((char*)&obj14,sizeof(obj14));
	fw.write((char*)&obj15,sizeof(obj15));
	fw.write((char*)&obj16,sizeof(obj16));
	fw.write((char*)&obj17,sizeof(obj17));
	fw.write((char*)&obj18,sizeof(obj18));
	fw.write((char*)&obj19,sizeof(obj19));
	fw.write((char*)&obj20,sizeof(obj20));
	fw.write((char*)&obj21,sizeof(obj21));
	fw.write((char*)&obj22,sizeof(obj22));
	fw.write((char*)&obj23,sizeof(obj23));
	fw.write((char*)&obj24,sizeof(obj24));
	fw.write((char*)&obj25,sizeof(obj25));
	fw.write((char*)&obj26,sizeof(obj26));
	fw.write((char*)&obj27,sizeof(obj27));
	fw.write((char*)&obj28,sizeof(obj28));
	fw.write((char*)&obj29,sizeof(obj29));
	fw.write((char*)&obj30,sizeof(obj30));
	fw.write((char*)&obj31,sizeof(obj31));
	fw.write((char*)&obj32,sizeof(obj32));
	fw.write((char*)&obj33,sizeof(obj33));
	fw.write((char*)&obj34,sizeof(obj34));
	fw.write((char*)&obj35,sizeof(obj35));
	fw.write((char*)&obj36,sizeof(obj36));
	fw.write((char*)&obj37,sizeof(obj37));
	fw.write((char*)&obj38,sizeof(obj38));
	fw.write((char*)&obj39,sizeof(obj39));
	fw.write((char*)&obj40,sizeof(obj40));
	fw.write((char*)&obj41,sizeof(obj41));
	fw.write((char*)&obj42,sizeof(obj42));
	fw.write((char*)&obj43,sizeof(obj43));
	fw.write((char*)&obj44,sizeof(obj44));
	fw.write((char*)&obj45,sizeof(obj45));
	fw.write((char*)&obj46,sizeof(obj46));
	fw.write((char*)&obj47,sizeof(obj47));
	fw.write((char*)&obj48,sizeof(obj48));
	fw.write((char*)&obj49,sizeof(obj49));
	fw.write((char*)&obj50,sizeof(obj50));
fw.close();
}
void rules(){
cout << "You have 500 coins to buy as many Pokemon of your choice."<<'\n';
cout << "Your aim is to defeat as many Pokemon as possible with the team you have built."<<'\n';
cout << "The available types of Pokemon are: "<<'\n';
cout << "Grass/Bug, Fighting, Flying, Fire, Water, Fairy, Psychic, Dragon"<<'\n';
cout << "Some Pokemon are especially stronger against certain types."<<'\n';
cout << "The type effectiveness chart is given below:"<<'\n'<<'\n';
cout <<"Type            Strong against"<<'\n';
cout << "Grass/bug      Psychic"<<'\n';
cout << "Psychic        Fighting, Poison"<<'\n';
cout << "Fairy          Fighting, Dragon"<<'\n';
cout << "Ground         Fire, Flying"<<'\n';
cout << "Poison         Fairy"<<'\n';
cout << "Grass          Water"<<'\n';
cout << "Fire           Grass, Poison"<<'\n';
cout << "Electric       Flying, Water"<<'\n';
cout << "Flying         Grass, Poison"<<'\n';
}
char removepok(int &count, pokemon array[], int &coins);
pokemon pick(int ct);
//main code
void main() {
clrscr();
int op=0;
do{   clrscr();
cout<<'\n';
cout <<'\t'<<'\t'<<'\t'<<"     WELCOME TO POKEBATTLE"<<'\n';
cout <<'\n'<<'\n'<<'\n'<<'\n'<<'\n'<<'\n';
cout <<'\t'<<'\t'<<'\t'<<'\t'<<"1. ADMIN MODE"<<'\n';
cout <<'\n';
cout <<'\t'<<'\t'<<'\t'<<'\t'<<"2. PLAYER MODE"<<'\n';
cout << '\t'<<'\t'<<'\t'<<'\t';

cin >> op;
if (op<1||op>2)
	{cout<<"Invalid option! Enter again: ";}
}while(op<1||op>2);


if (op==1)
{
initialise();
int i=0;
char pass[15];

cout <<"Welcome to admin mode"<<'\n';
do{
cout << "Enter the password: ";
int p=0;
do
	{
	pass[p]=getch();
	if ((int)pass[p]!=13)  //as long as newline character is not entered
		{
		cout<<"*";
		}
	p++;
	}while((int)pass[p-1]!=13);
	pass[p-1]='\0';
if(!strcmp(pass,"pokeme123"))
	{
	cout <<'\n'<<"ACCESS GRANTED"<<'\n';
	i=4;         //this is a check
	delay(1000);
	}
else
	{
	cout <<'\n'<<"ACCESS DENIED"<<'\n';
	i++;
	if (i==3)
		{
		cout<<"Too many wrong tries! Exiting... "<<'\n';
		delay(1000);
		exit(0);
		}
	}
}while(i<3);
if (i==4)
	{
	char yn='y';
	do
	{
	clrscr();
	cout <<"1. Modify pokemon details"<<'\n';
	cout <<"2. Delete a pokemon"<<'\n';
	cout <<"3. Player Scores"<<'\n';
	cout <<"4. Clear leaderboard"<<'\n';
	int ch;
	cin >> ch;
	if(ch==1)
		{
		modify();
		}
	else if(ch==2)
		{
		deletepok();
		}
	else if(ch==3)
		{
		ifstream fw;
		player ob;
		int i=0;
		fw.open("players.dat",ios::in|ios::binary);
		while(fw)
			{
			fw.read((char*)&ob,sizeof(player));
			i++;
			}
		fw.close();
		if (i==0)
			{
			cout<<"No players on the leaderboard. "<<'\n';
			}
		else
			{
			leaderboard();
			}
		}
	else if (ch==4)
		{
		remove("players.dat");
		cout<<"Leaderboard cleared. "<<'\n';
		}
	else
		{
		cout<<"Incorrect option! ";
		}
	cout<<"Do you want to continue? (y/n) ";
	cin>>yn;
	}while(tolower(yn)!='n');
	}

}



else if (op==2) //player mode
{
player p;
cout<<"Enter your name: ";
cin>>p.playername;
cout<<"Your name is : "<<p.playername<<'\n';
pokemon array[5];
randomize();
int choice;
char buynot='p';
char cont;
int coins=500;
int i=0; int count=0; //count is the no of pokemons the user has
int ct;               //ct is the number of pokemons in the file
rules();
cout<<"1. Continue to game"<<'\n'<<"2. Exit"<<'\n';
cin>>i;
if (i>2||i<1)
	{
	cout<<"Invalid option entered!! Continuing to game...";
	delay(2000);
	}
if (i==2)
	{
	cout<<"Game ending... ";
	delay(2000);
	exit(0);
	}
i=0;
clrscr();
cout<<"Welcome to Pokebattle!"<<'\n'<<"You have 500 coins. Use them wisely!"<<'\n';
while ((cont!='y'&&cont!='Y')&&(coins>0)) {
cout<<"Choose a pokemon: "<<'\n';
	ifstream f;
	pokemon pok;
	ct=0;
	f.open("pro.dat",ios::in|ios::binary);
	while(f.read((char*)&pok,sizeof(pokemon)))
		{
		ct++;
		cout<<pok.getid()<<". ";
		pok.printname();
		cout<<'\t';
		if (ct%3==0)
			{
			cout<<'\n';
			}
		}
	f.close();
	cout<<'\n';
//read the objects, display their attributes
	cin>>choice;
	int check=0;
	fstream fw;
	fw.open("pro.dat",ios::in|ios::binary);
	while(fw) {
	fw.read((char*)&pok,sizeof(pokemon));
	if (pok.getid()==choice)
		{
		pok.display();
		check=1;
		do{
			cout<<"Buy (B) or not (N)? ";
		cin>>buynot;
		if (tolower(buynot)!='b'&& tolower(buynot)!='n')
			{
			cout<<"Wrong option! Enter again... "<<'\n';
			}
		}while(tolower(buynot)!='b'&& tolower(buynot)!='n');
		if (tolower(buynot)=='b')
			{
			if (pok.getcost()>coins)
				{
				cout<<"You don't have enough coins for this. ";
				fw.close();
				i++;
				break;
				}
			else
				{
				coins=coins-pok.getcost();
				cout<<"You now have "<<coins<<" coins."<<'\n';
				array[i]=pok;
				i++;
				count++;
				fw.close();
				}
			}
		else if (tolower(buynot)=='n')
			{
			fw.close();
			}
		}
	}
if (check==0)
	{
	cout<<"This pokemon id not found. Please enter another. "<<'\n';
	}
char yn='y';
if (count>0) {
do{
cout<<"Now you have: "<<'\n';
if (count==0)
	{
	cout<<"no pokemons. "<<'\n';
	yn='n';
	}
for (i=0;i<count;i++)
	{
	cout<<i+1<<". ";
	array[i].printname();
	cout<<'\n';
	}
if (count>0)
	{
	yn=removepok(count, array, coins);
	}
}while (yn!='n'&&yn!='N');
if(count>0){
cout<<"Start playing(y) or not(n)?"<<'\n';
cin >> cont;
}
}
}
cout<<"You have a total of "<<count<<" pokemons. "<<'\n';
//delay here
clrscr();
i=0;
int beaten=0;
int ext1=0;
int ext2=0;
pokemon battle=pick(ct);
while(i<count)
	{
	 ext1 = extra(array[i].type,battle.type);
	 ext2 = extra(array[i].type,battle.type);

		int movechoice=5;
			do
			{
			do{
			cout << '\n'<<'\n';
			cout << "Your pokemon: "; array[i].printname();
			cout<<'\t'<<'\t'<<'\t'<<"Opponent: "; battle.printname();
			cout<<'\n';
			cout << "Pokemon Type: "<<array[i].type<<'\t'<<'\t'<<'\t'<<"Opponent Type: "<<battle.type<<'\n';
			cout <<'\n'<<'\n';
			cout <<'\n';
			cout<<'\t'<<'\t'<<"Choose a move to play...(1, 2, 3, 4)"<<'\n';
			array[i].displaymoves();
			cout << '\t'<<'\t';
			cin>>movechoice;
			if (movechoice>=5 || movechoice<0)
				{
				cout<<"Invalid option! Enter again... "<<'\n';
				delay(1000);
				clrscr();
				}
			  }while (movechoice>=5 || movechoice<0);
			if (movechoice==1)
				{
				cout <<'\t'<<'\t'; array[i].printname();
				cout << " used "; array[i].pmove.printmname1(); cout<<'\n';
				battle.health=battle.health-array[i].pmove.dmg1-ext1;
				array[i].health = array[i].health-5;
				}
			else if (movechoice==2)
				{
				cout <<'\t'<<'\t'; array[i].printname();
				cout << " used "; array[i].pmove.printmname2(); cout<<'\n';
				battle.health=battle.health-array[i].pmove.dmg2-ext1;
				array[i].health = array[i].health-10;
				}
			else if (movechoice==3)
				{
				cout <<'\t'<<'\t'; array[i].printname();
				cout << " used "; array[i].pmove.printmname3(); cout<<'\n';
				battle.health=battle.health-array[i].pmove.dmg3-ext1;
				array[i].health = array[i].health-15;
				}
			else if (movechoice==4)
				{
				cout <<'\t'<<'\t'; array[i].printname();
				cout << " used "; array[i].pmove.printmname4(); cout<<'\n';
				battle.health=battle.health-array[i].pmove.dmg4-ext1;
				array[i].health = array[i].health-20;
				}
			else if (movechoice==0)
				{
				cout << "Exiting.."<<'\n';
				delay(1500);
				exit(0);
				}

			int randmove=random(4)+1;
			if (randmove==1)
				{
				cout << '\t'<<'\t'; battle.printname();
				cout << " used "; battle.pmove.printmname1(); cout<<'\n';
				array[i].health=array[i].health-battle.pmove.dmg1-ext2;
				}
			if (randmove==2)
				{
				cout << '\t'<<'\t'; battle.printname();
				cout << " used "; battle.pmove.printmname2(); cout<<'\n';
				array[i].health=array[i].health-battle.pmove.dmg2-ext2;
				}
			if (randmove==3)
				{
				cout << '\t'<<'\t'; battle.printname();
				cout << " used "; battle.pmove.printmname3(); cout<<'\n';
				array[i].health=array[i].health-battle.pmove.dmg3-ext2;
				}
			if (randmove==4)
				{
				cout << '\t'<<'\t'; battle.printname();
				cout << " used "; battle.pmove.printmname4(); cout<<'\n';
				array[i].health=array[i].health-battle.pmove.dmg4-ext2;
				}
				if(array[i].health>0){
			cout<<'\t'<<'\t'<<"Your health is now "<<array[i].health<<'\n';
			}
			cout<<'\t'<<'\t'<<"Your opponent's health is now "<<battle.health<<'\n';

			delay(1500);
			clrscr();
			}while(battle.health>=0&&array[i].health>=0);
		if (array[i].health<=0)
			{
			i++;
			if (i<count)
				{
				cout<<'\t'<<'\t'<<"You lost!!! Moving to your next pokemon..."<<'\n';
				delay(2000);
				clrscr();
				}
			}
		else if (battle.health<0)
			{
			battle=pick(ct);
			cout<<'\t'<<'\t'<<"You won!!! Next opponent is coming..."<<'\n';
			beaten++;
			delay(2000);
			clrscr();
			}
	}
cout<<'\t'<<'\t'<<"Total pokemons you beat: "<<beaten<<'\n'<<"Nice job!"<<'\n';
p.putscore(beaten);
ofstream fw;
fw.open("players.dat",ios::ate|ios::binary);
fw.write((char*)&p,sizeof(player));
fw.close();
}
getch();
}

pokemon pick(int ct)
	{
	pokemon returnval;
	pokemon battle;
	do{
	randomize();
	int rand=random(ct)+1;
	ifstream fw;
	fw.open("pro.dat",ios::in|ios::binary);
	while(fw)
		{
		fw.read((char*)&battle,sizeof(pokemon));
		if (battle.getid()==rand&&battle.getid()!=0)
			{
			cout<<"Your next opponent is "; battle.printname();
			cout<<'\n';
			returnval=battle;
			break;
			}
		}
	fw.close();
	}while (battle.getid()==0);
	return returnval;
	}

char removepok(int &count, pokemon array[], int &coins)
	{
	char yn;
	cout<<"Do you want to remove any pokemons? (y/n) ";
	cin>>yn;
	if (yn=='y'||yn=='Y')
		{
		int no,i;
		cout<<"Enter pokemon no. to be deleted: ";
		cin>>no;
		if (no>count||no<1)
			{
			cout<<"Invalid option. "<<'\n';
			}
		else
			{
			no--;
			coins=coins+array[no].getcost();
			for (i=no;i<4;i++)
				{
				array[i]=array[i+1];
				}
			count--;
			}
		}
	return yn;
	}