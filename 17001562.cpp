#include<iostream>
#include<fstream>
#include <sstream>
#include<cmath>
using namespace std;
const int MAXSUBJECT=10;
const int MAXSTUDENT=100;
class Student{
	public:

		//******public variable*******
		int indexnum;
		int mark;
		char grade;

		//*******public functions*******
		Student(int index,int ma);//constructor
		void PrintDetail();

	private:
		//******private functoin*******
		void GiveGrade();
		
};
class Subject{
	public:
		//*********public variable*********
		string subcode,summary;

		//*********public function***********
		void ShowSubDetail();	
		void PrintStuDetail();
		void ShowStudent(int id);
        Subject(string * value);
        void CalculateSum();
		
	private:
		
		//*********private variable************
        int numberofstudent;
		int total,numberofA,numberofB,numberofC,numberofD,numberofF;
        float standarddeviation;
		
		//**********Student class pointers array**********
        Student ** studentdetail;
        
		//*********private function************    
        void Sort();
		float FindeAvg();
		void FindStandDevi();
		float rounded(float);

};
Student::Student(int index,int ma){
	indexnum=index;
	mark=ma;
	GiveGrade();
}

void Student::PrintDetail(){
	cout<<"\t\t"<<indexnum<<"\t"<<mark<<"\t"<<grade<<endl<<endl;
}
void Student::GiveGrade(){
	if(mark<30){
		grade='F';
	}else if(mark<40){
		grade='D';
	}else if(mark<55){
		grade='C';
	}else if(mark<70){
		grade='B';
	}else{
		grade='A';
	}
}


void Subject::Sort(){
    for(int i=0;i<numberofstudent-1;i++){
        for(int j=0;j<numberofstudent-i-1;j++){
            if(studentdetail[j]->indexnum>studentdetail[j+1]->indexnum){
                Student * temp=studentdetail[j];
                studentdetail[j]=studentdetail[j+1];
                studentdetail[j+1]=temp;
            }
        }
    }
}
float Subject::FindeAvg(){
    float avg=(float)total/numberofstudent;
    return avg;
}
void Subject::FindStandDevi(){
    float mean=FindeAvg();
    float temptotal;
    for(int i=0;i<numberofstudent;i++){
        float temp=(float)studentdetail[i]->mark-mean;
        temp=temp*temp;
        temptotal+=temp;

    }
    temptotal=temptotal/(float)numberofstudent;
    standarddeviation=sqrt(temptotal);
}
void Subject::CalculateSum(){
    summary=subcode;
    stringstream s1;
    s1<<numberofstudent;
	summary=summary+" "+s1.str();
    float temp=((float)numberofA/(float)numberofstudent)*100.0;
	temp=rounded(temp);
    stringstream s2;
    s2<<temp;
    summary+=" A "+s2.str();
    stringstream s3;
    temp=((float)numberofB/(float)numberofstudent)*100.0;
	temp=rounded(temp);
    s3<<temp;
    summary+="% B "+s3.str();
    stringstream s4;
    temp=((float)numberofC/(float)numberofstudent)*100.0;
	temp=rounded(temp);
    s4<<temp;
    summary+="% C "+s4.str();
    stringstream s5;
	temp=((float)numberofD/(float)numberofstudent)*100.0;
	temp=rounded(temp);
    s5<<temp;
    summary+="% D "+s5.str();
    stringstream s6;
    temp=((float)numberofF/(float)numberofstudent)*100.0;
	temp=rounded(temp);
    s6<<temp;
    summary+="% F "+s6.str()+"%\n";
}
float Subject::rounded(float input){
	int output=(int)((input*10)+0.5);
	return (float)((output)/10.0);
}
Subject::Subject(string * value){
    total=numberofA=numberofB=numberofC=numberofD=numberofF=0;
	subcode=value[0].substr(0,7);
    stringstream temp(value[0].substr(8,2));
    temp>>numberofstudent;
    studentdetail=new Student* [numberofstudent];
                
    int i=1;
    while(i<=numberofstudent){
        stringstream stud(value[i].substr(0,8));
        int index;
        stud>>index;
        int mark;
        stringstream stu(value[i].substr(9,2));
        stu>>mark;
        total+=mark;
        studentdetail[i-1]=new Student(index,mark);
        i++;
        if(mark<30){
            numberofF++;
        }else if(mark<40){
           	numberofD++;
        }else if(mark<55){
            numberofC++;
        }else if(mark<70){
            numberofB++;
        }else{
            numberofA++;
        }
                    
    }
	FindStandDevi();
    Sort();

}
void Subject::ShowSubDetail(){
	cout<<"\t*******Subjectcode:"<<subcode<<"********"<<endl<<endl;
	cout<<"\t\tNumber of student:"<<numberofstudent<<endl<<endl;
	cout<<"\t\tAverage:"<<FindeAvg()<<endl<<endl;
	cout<<"\t\tStandard Deviation:"<<standarddeviation<<endl<<endl;
	cout<<"\t\tNumber of A:"<<numberofA<<endl<<endl;
	cout<<"\t\tNumber of B:"<<numberofB<<endl<<endl;
	cout<<"\t\tNumber of C:"<<numberofC<<endl<<endl;
	cout<<"\t\tNumber of D:"<<numberofD<<endl<<endl;
	cout<<"\t\tNumber of F:"<<numberofF<<endl<<endl;
}
void Subject::ShowStudent(int id){
	for(int i=0;i<numberofstudent;i++){
		if(studentdetail[i]->indexnum==id){
			cout<<"\t"<<subcode<<"\t\t"<<studentdetail[i]->mark<<endl;
			return;
		}
	}
	cout<<"\t"<<subcode<<"\t\tNot found."<<endl;
}
void Subject::PrintStuDetail(){
	for(int i=0;i<numberofstudent;i++){
	studentdetail[i]->PrintDetail();
	}
}

int main(){
	int maxline=MAXSUBJECT*MAXSTUDENT;

	string inputfile[maxline];
	ifstream inputf;

	inputf.open("test.txt");
	
	int count =0;

	while(!inputf.eof()){
		getline(inputf,inputfile[count++]);
	}
	int numberofsubject=0;
	int i=0;
	
	while(i<count){
		stringstream temp(inputfile[i].substr(8,3));
		int j;
		temp>>j;
		if(j>MAXSTUDENT){
			cout<<"There are more than data we expected,therefore cannot run the system."<<endl;
			return 0;
		}
		i=i+j+1;
		numberofsubject++;
	}
	if(numberofsubject>MAXSUBJECT){
		cout<<"There are more than data we expected,therefore cannot run the system."<<endl;
		return 0;
	}
	i=0;
	int j=0;

	Subject * subjectarr[numberofsubject];
	while(i<count){
		subjectarr[j++]=new Subject(&inputfile[i]);
		stringstream temp(inputfile[i].substr(8,2));
		int k;
		temp>>k;
		i=i+k+1;
	}
	
	int option=1;
	while(1){
		cout<<"\t......Select what are you going to do.......\n"<<endl;
		cout<<"\t......1 for Display Subject................."<<endl;
		cout<<"\t......2 for Display Student................."<<endl;
		cout<<"\t......3 for Display Subject Summary........."<<endl;
		cout<<"\t......4 for Save Summaries.................."<<endl;
		cout<<"\t......0 for Exit programe..................."<<endl<<endl<<"\t\tEnter:";
		cin>>option;
		if(option==1){
			string tempsubcode;
			cout<<"Enter your subject code:";
			cin>>tempsubcode;
			int i;
			for(i=0;i<numberofsubject;i++){
				if(subjectarr[i]->subcode==tempsubcode){
				//	subjectarr[i]->PrintStuDetail();
					break;
				}
			}
			if(i>=numberofsubject){
				cout<<".........This subject does not exist in over list..........."<<endl;
			}else{
				cout<<"\t\t"<<"INDEXNUMBER"<<"\t"<<"MARK"<<"\t"<<"GRADE"<<endl<<endl;
					for(i=0;i<numberofsubject;i++){
					if(subjectarr[i]->subcode==tempsubcode){
						subjectarr[i]->PrintStuDetail();
						break;
					}
				}
			}
			cout<<"Press Enter button to continue............"<<endl;
			getchar();
			while(!getchar());


		}else if(option==2){
			int stuind;
			cout<<"Enter student index:";
			cin>>stuind;
			cout<<"\tSubject Code\tMarks"<<endl;
			for(int i=0;i<numberofsubject;i++){
				subjectarr[i]->ShowStudent(stuind);
			}
			cout<<"Press enter to continue."<<endl;
			getchar();
			while(!getchar());

		}else if(option==3){
			string subcode;
			cout<<"Enter Subject code:";
			cin>>subcode;
			cout<<endl<<endl;
			int i;
			for(i=0;i<numberofsubject;i++){
				if(subjectarr[i]->subcode==subcode){
					subjectarr[i]->ShowSubDetail();
					break;
				}
			}
			if(i==numberofsubject){
				cout<<"NOT FOUND"<<endl;
			}
			cout<<"Press enter to continue.......";
			getchar();
			while(!getchar());

		}else if(option==4){
			ofstream newfile;
			newfile.open("summdata.txt");
			for(int i=0;i<numberofsubject;i++){
				subjectarr[i]->CalculateSum();
				//cout<<subjectarr[i]->summary<<endl;
				cout<<"Summary:"<<subjectarr[i]->summary<<endl;
				newfile<<subjectarr[i]->summary;
			}
			newfile.close();
			cout<<"Succesefully data added to file."<<endl<<"Press enter to continue............"<<endl;
			getchar();
			while(!getchar());
		}else if(option==0){
			break;
		}else{
			cout<<"\t.............INVALID INPUT...................."<<endl;
		}
	}
	
	
}
	
	

