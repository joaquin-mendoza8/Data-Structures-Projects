#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

class Racer{
    
    private:

        // private member variables
        string horseName;
        string jockeyName;
        double horseWeight;
        double jockeyWeight;
        int horseAge;
        char horseGender;
        bool defeat;
        bool injured;
        bool allowed;

    public:

        // default constructor
        Racer(): defeat(false), injured(false), allowed(true) {}

        // explicit constructor
        Racer(string horseName, string jockeyName, double horseWeight, double jockeyWeight, int horseAge, char horseGender) : \
        horseName(horseName), jockeyName(jockeyName), horseWeight(horseWeight), jockeyWeight(jockeyWeight), horseAge(horseAge), horseGender(horseGender), \
        defeat(false), injured(false), allowed(true) {}
        
        // neatly prints Racer instance's attributes
        void print() const{
            cout << "Horse Name: " << horseName << endl;
            cout << "Jockey Name: " << jockeyName << endl;
            cout << "Horse Weight: " << horseWeight << endl;
            cout << "Jockey Weight: " << jockeyWeight << endl;
            cout << "Horse Age: " << horseAge << endl;
            cout << "Horse Gender: " << horseGender << endl;
            cout << "Defeated: " << defeat << endl;
            cout << "Injured: " << injured << endl;
            cout << "Allowed to Race: " << allowed << "\n\n";
        }
            
        // increments horse age, determines injured status, and 
        // allowed status
        void age_me(){

            // increments object's age
            horseAge++;

            // determines chance of injury by horseAge
            if(horseAge < 6){
                injured = (rand()%4) == 0;
            }else if(horseAge <= 13){
                injured = (rand()%100) <= 2;
            }else{
                injured = (rand()%10) <= 7;
            }

            // allowed to race if not injured
            allowed = !injured;
        }

        // Creates race between two racer objects
        void race(Racer& other){

            // prevents unallowed/injured racers from racing
            if(!(other.allowed && allowed) || injured || other.injured){
                cout << "Race cancelled: One of the horses is injured or unallowed to race.\n\n";
                return;
            }

            // fight ratio between racers
            int fight_ratio = ((horseWeight + jockeyWeight) \
            /(other.horseWeight + other.jockeyWeight)) * 50;

            // random int (1-100)
            int rand_val = rand()%100 + 1;

            // calling racer wins if rand < fight ratio
            if(rand_val < fight_ratio){
                other.defeat = true;
                cout << horseName << " wins!\n\n";
            }else{
                // otherwise, other racer wins
                defeat = true;
                cout << horseName << " wins!\n\n";
            }
        }
        

        // member variable accessors
        string getHorseName() const {return horseName;};
        string getJockeyName() const {return jockeyName;};
        double getHorseWeight() const {return horseWeight;};
        double getJockeyWeight() const {return jockeyWeight;};
        int getHorseAge() const {return horseAge;};
        char getHorseGender() const {return horseGender;};
        bool getDefeat() const {return defeat;};
        bool getInjured() const {return injured;};
        bool getAllowed() const {return allowed;};

        // set name of horse
        void setHorseName(string name) {
            cout << "The horse, " << horseName;
            horseName = name;
            cout << ", is now named " << horseName << "\n\n";
        };

        // set name of jockey
        void setJockeyName(string name) {
            cout << "The jockey, " << jockeyName;
            jockeyName = name;
            cout << ", is now named " << jockeyName << "\n\n";
        }

        // set weight of horse to valid weight
        void setHorseWeight(double weight){
            if(weight <= 0){
                cout << "ERROR: Invalid weight\n\n";
                return;
            }
            horseWeight = weight;
            cout << horseName << " now weighs " << horseWeight << "\n\n";
        }

        // set weight of jockey to valid weight
        void setJockeyWeight(double weight){
            if(weight <= 0){
                cout << "ERROR: Invalid weight\n\n";
                return;
            }
            jockeyWeight = weight;
            cout << jockeyName << " now weighs " << jockeyWeight << "\n\n";
        }

        // set age of horse to valid age
        void setHorseAge(int age){
            if(age <= 0){
                cout << "ERROR: Invalid age\n\n";
                return;
            }
            horseAge = age;
            cout << horseName << " is now age " << horseAge << "\n\n";
        }

        // set gender of horse (either 'f' or 'm')
        void setHorseGender(char c){
            if(!(c == 'm' && c == 'f')){
                cout << "Input must be either 'm' or 'f'" << "\n\n";    
                return;
            }
            if(horseGender == 'f' && c == 'm'){
                horseGender = 'm';
                cout << horseName << " is now male\n\n";
            }else if(horseGender == 'm' && c == 'f'){
                horseGender = 'f';
                cout << horseName << " is now female\n\n";
            }
        }

        // set status of defeat
        void setDefeat(bool val){
            if(val && !defeat){
                defeat = true;
                cout << horseName << "'s injured status now set to " << defeat << "\n\n";
            }else if (!val && defeat){
                defeat = false;
                cout << horseName << "'s injured status now set to " << defeat << "\n\n";
            }else{
                cout << horseName << "'s injured status is already "  << defeat << "\n\n";
            }
        }

        // set injured status
        void setInjured(bool val){
            if(val && !injured){
                injured = true;
                allowed = false;
                cout << horseName << "'s injured status now set to " << injured << "\n\n";
            }else if (!val && injured){
                injured = false;
                allowed = true;
                cout << horseName << "'s injured status now set to " << injured << "\n\n";
            }else{
                cout << horseName << "'s injured status is already "  << injured << "\n\n";
            }
        } 

        // set allowed-to-race status
        void setAllowed(bool val){
            if(val && !allowed){
                allowed = true;
                injured = false;
                cout << horseName << "'s allowed status now set to " << allowed << "\n\n";
            }else if (!val && allowed){
                allowed = false;
                injured = true;
                cout << horseName << "'s allowed status now set to " << allowed << "\n\n";
            }else{
                cout << horseName << "'s allowed status is already "  << allowed << "\n\n";
            }
        }
};  

int main(){
    
    // set booleans to boolalpha
    cout << boolalpha << endl;

    // seed random function
    srand((unsigned int)time(0));

    // create racer objects
    Racer r1("Harry", "Hermione", 185.5, 6.73, 15, 'f');
    Racer r2("Ron", "Snape", 185.5, 6.73, 15, 'f');

    // ages racer objects
    r1.age_me();
    r2.age_me();

    // prints racer objects
    r1.print();
    r2.print();

    // calls mutator methods
    r1.setHorseName("Malfoy");
    r1.setJockeyName("Lupin");
    r1.setHorseWeight(200);
    r1.setJockeyWeight(140);
    r1.setHorseAge(3);
    r1.setHorseGender('m');
    r1.setDefeat(false);
    r1.setInjured(false);
    r1.setAllowed(true);

    // calls accessor methods
    cout << "Access to horseName: " << r1.getHorseName() << endl;
    cout << "Access to jockeyName: " << r1.getJockeyName() << endl;
    cout << "Access to horseWeight: " << r1.getHorseWeight() << endl;
    cout << "Access to jockeyWeight: " << r1.getJockeyWeight() << endl;
    cout << "Access to horseAge: " << r1.getHorseAge() << endl;
    cout << "Access to horseGender: " << r1.getHorseGender() << endl;
    cout << "Access to defeat: " << r1.getDefeat() << endl;
    cout << "Access to injured: " << r1.getInjured() << endl;
    cout << "Access to allowed: " << r1.getAllowed() << "\n\n";

    // races two objects against each other
    r1.race(r2);

    return 0;
}