//
//  vehicle.cpp
//  Homework3
//
//  Created by Impana on 2/13/23.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

class Vehicle{
    public:
        Vehicle(string id){
            m_id = id;
        }
        virtual string id() const{
            return m_id;
        }
        virtual string description() const = 0; //pure virtual
        virtual bool canHover() const{
            string desc = description();
            return(desc=="a drone"|desc=="a small balloon"|desc=="a large balloon");
        }
        virtual ~Vehicle(){}
    private:
        string m_id;
};

class Drone : public Vehicle{
    public:
        Drone(string id) : Vehicle(id){}
        virtual string description() const{
            return "a drone";
        }
        virtual ~Drone(){
            cout << "Destroying " << id() << ", " << description() << endl;
        }
};

class Balloon : public Vehicle{
    public:
        Balloon(string id, float diam) : Vehicle(id){
            m_diam = diam;
        }
        virtual string description() const{
            if (m_diam < 8)
                return "a small balloon";
            return "a large balloon";
        }
        virtual ~Balloon(){
            cout << "Destroying the balloon " << id() << endl;
        }
    private:
        float m_diam;
};

class Satellite : public Vehicle{
    public:
        Satellite(string id) : Vehicle(id){}
        virtual string description() const{
            return "a satellite";
        }
        virtual ~Satellite(){
            cout << "Destroying the " << description().substr(2) << " " << id() << endl;
        }
};

void display(const Vehicle* v)
{
    cout << v->id() << " is " << v->description();
    if (v->canHover())
        cout << ", so it can hover";
    cout << endl;
}

int main()
{
    Vehicle* fleet[4];
    fleet[0] = new Drone("CB4UP");
    //fleet[0] = new Vehicle("56-6693")); //should have compilation error
      // Balloons have an id and a diameter in meters  Balloons with a
      // diameter under 8 meters are small balloons; those with a diameter
      // 8 meters or more are large balloons
    fleet[1] = new Balloon("99LB", 6.3);
    fleet[2] = new Balloon("CN20230201", 30.2);
    fleet[3] = new Satellite("EB8675309");

    for (int k = 0; k < 4; k++)
        display(fleet[k]);

      // Clean up the vehicles before exiting
    cout << "Cleaning up" << endl;
    for (int k = 0; k < 4; k++)
        delete fleet[k];
}

