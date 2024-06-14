#include<iostream>
#include<ctype.h>
#include<iomanip>

using namespace std;
int PLAN = 0;
int CLIENT = 0;
int POSITION = 0;

class TrainingPLAN{
    string TPName;
    int SessionPERWEEK;
    float FeesPerWeek;
    public:
        TrainingPLAN(){
            TPName = "";
            SessionPERWEEK = 0;
            FeesPerWeek = 0;
        }
        
        void swap(TrainingPLAN &p1, TrainingPLAN &p2){
            TrainingPLAN swapped = p1;
            p1 = p2;
            p2 = swapped;
        }
        int partition(TrainingPLAN arr[],int low,int high){
            TrainingPLAN pivot=arr[high];
            int i=(low-1);
            for(int j=low;j<=high;j++){
              if(arr[j].getFeesPerWeek()<pivot.getFeesPerWeek()){
                i++;
                swap(arr[i],arr[j]);
              }
            }
            swap(arr[i+1],arr[high]);
            return (i+1);
        }

        void quickSort(TrainingPLAN arr[],int low,int high){
            if(low<high){
                int pi=partition(arr,low,high);
                quickSort(arr,low,pi-1);
                quickSort(arr,pi+1,high);
            }
        }
        TrainingPLAN(string n, int s, float FPW, TrainingPLAN plans[]){
            TPName = n;
            SessionPERWEEK = s;
        	FeesPerWeek = FPW;
            quickSort(plans, 0, PLAN-1);
        }
        void setPlan(TrainingPLAN plans[]){
            cout<<"Enter Plan Name = ";
            cin.get();
            getline(cin, TPName);
            cout<<"Enter Session Per WEEK = ";
            cin>>SessionPERWEEK;
            feeLabel:
            cout<<"Enter Fees Per Week = ";
            cin>>FeesPerWeek;
            cout<<"Successfully Created A Training PLAN("<<TPName<<")!\n";
            cin.get();
            PLAN++;
        }
        void UpdatePlan(){
            cout<<"Plan name("<<TPName<<") : \n";
            cout<<"Enter Sessions Per WEEK ("<<SessionPERWEEK<<") : ";
            cin>>SessionPERWEEK;
            FEELabel:
            cout<<"Enter Fees per week ("<<FeesPerWeek<<") : ";
            cin>>FeesPerWeek;
            cout<<"Successfully Added the training plan("<<TPName<<")!\n";
            cin.get();
        } 
        string getPlanName() {return TPName;}
        float getFeesPerWeek() {return FeesPerWeek;}
        int getSessionsPerWeek() {return SessionPERWEEK;}
        void displayPlan(){
            cout<<setw(20)<<TPName
                <<setw(20)<<SessionPERWEEK
                <<setw(15)<<FeesPerWeek;
        }
};

class Client{
    string cName;
    TrainingPLAN trainingPlan;
    float CurrentWeight;
    int PrivateHours[4];
    bool PrivateHourOnOff[4];
    int LearntPosesCount;
    string LearntPoses[10];
    float Costs;
    public:
        Client(){
            cName = "";
            CurrentWeight = 0;
            Costs = 0;
            LearntPosesCount = 0;
            for(int i=0; i<4; i++){
                PrivateHours[i] = 0;
                PrivateHourOnOff[i] = 0;
            }
        }
        Client(string n, TrainingPLAN tp, float w, int h[4], bool OnOff[4]){
            cName = n;
            trainingPlan = tp;
            CurrentWeight = w;
            LearntPosesCount = 0;
            Costs = 0;
            for(int i=0; i<4; i++){
                PrivateHours[i] = h[i];
                PrivateHourOnOff[i] = OnOff[i];
            }
            CLIENT++;
        }
        void addLearntPoses(string poses[]){
            char learnt = 'y';
            int ind = 0;
            int learntInd = 0;
            cout<<"Already learnt poses? (y/n) : ";
            cin>>learnt;
            if(learnt=='y') {
                for(int i=0; i<10; i++){
                    cout<<"("<<i+1<<")"<<poses[i];
                    if(i+1 != 10) cout<<" , ";
                }
                while(true){
                    char more = 'y';
                    cout<<"\nEnter pose index : ";
                    cin>>ind;
                    cout<<"Got more?(y/n) : ";
                    cin>>more;
                    LearntPosesCount++;
                    LearntPoses[learntInd] = poses[ind-1];
                    learntInd++;
                    if(more!='y') break;
                }
            }
            cout<<endl;
        }
        string setClient(TrainingPLAN plans[]){
            int PlanIndex = 0;
            cout<<"Enter Client name : ";
            cin.get();
            getline(cin, cName);

            TrainingPlanLabel:
            cout<<"Enter training plan - Available plans : \n";
            for(int i=0; i<PLAN; i++){
                cout<<"Plan : "<<i+1<<" "<<plans[i].getPlanName();
                if(i+1!=PLAN) cout<<" ,\n";
            }
            cout<<"\nChoose the index : ";
            if(PlanIndex < 0 || PlanIndex > PLAN) goto TrainingPlanLabel;
            cin>>PlanIndex;
            trainingPlan = plans[PlanIndex-1];

            cout<<"Enter Clients's Current weight = ";
            cin>>CurrentWeight;

            for(int i=0; i<4; i++){
                char o = '0';
                PrivateHourLabel:
                cout<<"Enter"<<i+1<<" th/st Week Private Hours : \n";
                cin>>PrivateHours[i];
                if(PrivateHours[i] < 0 || PrivateHours[i] > 5) {
                    cout<<"It exceeded 5 or less than 0\n";
                    goto PrivateHourLabel;
                }
                
                OnlineOfflineLabel:
                cout<<"Online/Offline(0/1) : ";
                cin>>o;
                if(o=='0') PrivateHourOnOff[i] = 0;
                else PrivateHourOnOff[i] = 1;
            }
            LearntPosesCount = 0;
            CLIENT++;
            return trainingPlan.getPlanName();
        }
        string updateClient(TrainingPLAN plans[]){
            int planIndex = 0;
            cout<<"Clinet name("<<cName<<") : \n";

            trainingPlanLabel:
            cout<<"Enter Training Plan - Available Plans : \n";
            for(int i=0; i<PLAN; i++){
                cout<<"Plan : "<<i+1<<" "<<plans[i].getPlanName();
                if(i+1!=PLAN) cout<<" ,\n";
            }
            cout<<"\nChoose the Index : ";
            if(planIndex < 0 || planIndex > PLAN) goto trainingPlanLabel;
            cin>>planIndex;
            trainingPlan = plans[planIndex-1];

            cout<<"Enter Current weight(kg) : ";
            cin>>CurrentWeight;

            for(int i=0; i<4; i++){
                char o = '0';
                cout<<"Enter"<<i+1<<" th/st Week Private Hours : \n";
                cin>>PrivateHours[i];
                OnlineOfflineLabel:
                cout<<"Online/Offline(0/1) : ";
                cin>>o;
                if(o=='0') PrivateHourOnOff[i] = 0;
                else PrivateHourOnOff[i] = 1;
            }
            LearntPosesCount = 0;
            return trainingPlan.getPlanName();
        }
        float getFinalCost(){
            Costs = 0;
            Costs += trainingPlan.getFeesPerWeek()*4;
            int Count = LearntPosesCount;
            if(Count > 5) Count = 5;
            for(int i=0; i<4; i++){
                if(PrivateHourOnOff[i]) Costs += 15000*PrivateHours[i];
                else Costs += 17000*PrivateHours[i];
            }
            return Costs - (Costs*Count)/100;
        }
        float getCost() {
            Costs = 0;
            Costs += trainingPlan.getFeesPerWeek()*4;
            
            for(int i=0; i<4; i++){
                if(PrivateHourOnOff[i]) Costs += 15000*PrivateHours[i];
                else Costs += 17000*PrivateHours[i];
            }
            return Costs;
        }
        void DisplayClient(){
            cout<<setw(20)<<cName
                <<setw(20)<<trainingPlan.getPlanName()
                <<setw(10)<<LearntPosesCount
                <<setw(20)<<getFinalCost();
        }
        void displayClientDetails(){
            int Online = 0, Offline = 0;
            for(int i=0; i<4; i++){
                if(PrivateHourOnOff[i]) Online++;
                else Offline++;
            }
            int Count = LearntPosesCount;
            if(Count > 5) Count = 5;
            cout<<setw(30)<<"Customer name : "<<setw(20)<<cName<<endl
                <<setw(30)<<"Weight : "<<setw(20)<<CurrentWeight<<endl
                <<setw(30)<<"Training plan : "<<setw(20)<<trainingPlan.getPlanName()<<endl
                <<setw(30)<<"Learnt poses counts : "<<setw(20)<<LearntPosesCount<<endl<<setw(30)<<"Learnt poses : ";
            for(int i=0; i<LearntPosesCount; i++) cout<<LearntPoses[i]<<", ";
            cout<<endl<<setw(30)<<"Sessions per week : "<<setw(20)<<trainingPlan.getSessionsPerWeek()
                <<setw(20)<<trainingPlan.getFeesPerWeek()*4<<endl
                <<setw(30)<<"Private (Online-15000) : "<<setw(20)<<Online<<setw(20)<<15000*Online<<endl
                <<setw(30)<<"Private (Offline-17000) : "<<setw(20)<<Offline<<setw(20)<<17000*Offline<<endl
                <<setw(30)<<"DISCOUNT (%) : "<<setw(20)<<LearntPosesCount<<setw(20)<<getCost()*Count/100<<endl
                <<setw(30)<<"Total Cost : "<<setw(20)<<""<<setw(20)<<getFinalCost()<<endl;
            cin.get();
        }
};
class Position{
    string name;
    int PoseCount;
    public:
    public:
        string PoseType[10];
        string PoseName[10];
        Position(){
            name = "";
            PoseCount = 0;
        }
        Position(string name, string type[10], string names[10], int pc){
            this->name = name;
            PoseCount = pc;
            for(int i=0; i<10; i++){
                PoseType[i] = type[i];
                PoseName[i] = names[i];
            }
            POSITION++;
        }
        void AddPosition(){
            cout<<"Position name : "<<name<<endl;
            cout<<"Positions : \n";
            for(int i=0; i<PoseCount; i++) {
                cout<<PoseName[i];
                if(i+1 != PoseCount) cout<<" , ";
                else cout<<endl;
            }
            if(PoseCount == 10) {
                cout<<"10 Poses Already Added\n";
                cin.get();
                return;
            }
            char more = 'y';
            while(true){
                cin.get();
                if(PoseCount==10) break;

                cout<<"Enter Position Name("<<PoseCount+1<<") : ";
                getline(cin,PoseName[PoseCount]);
                cout<<"Enter Position Type("<<PoseCount+1<<") : ";
                getline(cin,PoseType[PoseCount]);
                cout<<"Successfully Added("<<PoseName[PoseCount]<<")\n";
                PoseCount++;

                cout<<"Add more?(y/n) : ";
                cin>>more;
                if(more=='n') break;
            }
        }
        void CreatePosition(){
            cout<<"Enter Position Name : ";
            cin.get();
            getline(cin,name);
            POSITION++;
            AddPosition();
        }
        void DisplayPosition(){
            cout<<setw(20)<<name<<endl;
            for(int i=0; i<PoseCount; i++){
                cout<<setw(25)<<""
                    <<setw(20)<<PoseType[i]
                    <<setw(20)<<PoseName[i]
                    <<endl;
            }
        }
};
void DisplayTrainingPlans(TrainingPLAN plans[]);
void DisplayYogaPositions(Position Poses[]);
void DisplayClients(Client clients[]);

int main(){
    int menuCode;
    
    Position Poses[5];
    string basicPoseType[10] = {"Standing Pose","Standing Pose","Standing Pose","Standing Pose","Balancing Pose","Balancing Pose","Balancing Pose","Balancing Pose","Seat Pose","Backend Pose"};
    string basicPoseNames[10] ={"Archer Pose","Dolphin Pose","Frog Pose","Fallen Triangle","Big Toe Pose","Lion Pose","Airplane Pose","Side Lunge","Side Reclining","Bird Dog Pose"};
    Position pose1("BASIC",basicPoseType,basicPoseNames,10);
    
    string imPoseType[10] = {"Standing Pose","Standing Pose","Standing Pose","Standing Pose","Balancing Pose","Balancing Pose","Balancing Pose","Balancing Pose","Seat Pose","Backend Pose"};
    string imPoseNames[10] ={"Downward Facing Pose","Mountain Pose","Warrior Pose","Traingle Triangle","Low Lunge","Tree Pose","Plank Pose","Bridge Lunge","Staff Pose","Cobbler's Pose"};
    Position pose2("INTERMEDIATE",imPoseType,imPoseNames,10);
    
    Poses[0] = pose1;
    Poses[1] = pose2;
    
    TrainingPLAN plans[7];
    TrainingPLAN basic("BASIC",3,25000,plans);
    TrainingPLAN inter("INTERMEDIATE",3,35000,plans);
    TrainingPLAN advan("ADVANCED",2,50000,plans);
    plans[0] = basic;
    plans[1] = inter;
    plans[2] = advan;

    Client clients[50];
    int c1Private[4] = {1,1,3,2};
    bool c1OnOff[4] = {true,false,true,true};
    int c2Private[4] = {1,1,3,2};
    bool c2OnOff[4] = {true,true,true,false};
    int c3Private[4] = {1,1,3,2};
    bool c3OnOff[4] = {true,true,false,true};
    int c4Private[4] = {1,1,3,2};
    bool c4OnOff[4] = {false,false,true,true};
    int c5Private[4] = {1,1,3,2};
    bool c5OnOff[4] = {true,false,false,true};
    
    Client c1("Kaung Myat Wai",plans[0],55,c1Private,c1OnOff);
    Client c2("Zwe Hset",plans[0],55,c2Private,c2OnOff);
    Client c3("Thurein",plans[0],55,c3Private,c3OnOff);
    Client c4("Min ThiHa",plans[0],55,c4Private,c4OnOff);
    Client c5("Nyi Min Htet",plans[0],55,c5Private,c5OnOff);
    clients[0] = c1;
    clients[1] = c2;
    clients[2] = c3;
    clients[3] = c4;
    clients[4] = c5;

    menuLabel:
    cout<<"Welcome from Amazing Sport Yoga System!"<<endl
        <<setw(10)<<"1. Training plan."<<endl
        <<setw(10)<<"2. Clients"<<endl
        <<setw(9)<<"0. Leave Program\n";
    cin>>menuCode;
    if(menuCode==1) {
        TrainingPlanScreenLabel:
        int TrainingMenuCode = 0;
        cout<<"1. Add a Training plan.\n2. Show all training plans.\n3. Update a Praining plan.\n4. Add a Yoga Plan.\n5. Display yoga plans.\n6. Add yoga poses.\n0. Return to main screen.\n";
        cin>>TrainingMenuCode;
      
        if(TrainingMenuCode < 0 || TrainingMenuCode > 6) goto TrainingPlanScreenLabel;
        if(TrainingMenuCode == 0) goto menuLabel;
        else if(TrainingMenuCode == 1) plans[PLAN].setPlan(plans);
        else if(TrainingMenuCode == 2) DisplayTrainingPlans(plans);
        else if(TrainingMenuCode == 3) {
            int index = 0;
            DisplayTrainingPlans(plans);
            cout<<"Enter Number to Update : ";
            cin>>index;
            plans[index-1].UpdatePlan();
        }
        else if(TrainingMenuCode == 4) Poses[POSITION].CreatePosition();
        else if(TrainingMenuCode == 5) DisplayYogaPositions(Poses);
        else if(TrainingMenuCode == 6) {
            int index = 0;
            DisplayYogaPositions(Poses);
            cout<<"\nEnter yoga plan index to add : ";
            cin>>index;
            Poses[index-1].AddPosition();
        }
        goto TrainingPlanScreenLabel;
    } 
    else if(menuCode==2){
        clientScreenLabel:
        int clientScreenCode = 0;
        cout<<"1. Register a New Client.\n2. View all Clients.\n3. Update Client info.\n4. Calculate costs for the Client.\n0. Return to main screen. \n";
        cin>>clientScreenCode;
        if(clientScreenCode < 0 || clientScreenCode > 4) goto clientScreenLabel;
      
        if(clientScreenCode == 0) goto menuLabel;
        else if(clientScreenCode == 1) {
            string plan = clients[CLIENT].setClient(plans);
            if(plan=="INTERMEDIATE") clients[CLIENT-1].addLearntPoses(basicPoseNames);
            else if(plan=="ADVANCED") clients[CLIENT-1].addLearntPoses(imPoseNames);
        }
        else if(clientScreenCode == 2) DisplayClients(clients);
        else if(clientScreenCode == 3) {
            int index = 0;
            DisplayClients(clients);
            cout<<"Enter number to update : ";
            cin>>index;
            string plan = clients[index-1].updateClient(plans);
            if(plan=="INTERMEDIATE") clients[index-1].addLearntPoses(basicPoseNames);
            else if(plan=="ADVANCED") clients[index-1].addLearntPoses(imPoseNames);
        }
        else if(clientScreenCode == 4) {
            int index = 0;
            DisplayClients(clients);
            cout<<"Enter number to calculate costs : ";
            cin>>index;
            clients[index-1].displayClientDetails();
        }
        goto clientScreenLabel;
    }
    else if(menuCode==0) return 0;
    else goto menuLabel;
}

void DisplayTrainingPlans(TrainingPLAN plans[]){
    cout<<setw(5)<<"No"
        <<setw(20)<<"Plan name"
        <<setw(20)<<"Session per week"
        <<setw(15)<<"Fees per week"
        <<endl;
    for(int i=0; i<PLAN; i++) {
        cout<<setw(5)<<i+1;
        plans[i].displayPlan();
        cout<<endl;
    }
}

void DisplayYogaPositions(Position Poses[]){
    cout<<setw(5)<<"No"
        <<setw(20)<<"Position names"
        <<setw(20)<<"Pose type"
        <<setw(20)<<"Pose name"
        <<endl;
    for(int i=0; i<POSITION; i++) {
        cout<<setw(5)<<i+1;
        Poses[i].DisplayPosition();
        cout<<endl;
    }
}

void DisplayClients(Client clients[]){
    cout<<setw(5)<<"No"
        <<setw(20)<<"Customer name"
        <<setw(20)<<"Training plan"
        <<setw(10)<<"Learnt poses count"
        <<setw(20)<<"Cost(current month)"
        <<endl;
    for(int i=0; i<CLIENT; i++) {
        cout<<setw(5)<<i+1;
        clients[i].DisplayClient();
        cout<<endl;
    }
}