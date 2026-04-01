#include<iostream>
#include<string>
#include<vector>
#include"character.h"
#include"party.h"

void Party::getINFO() const{
    warrior.getINFO();
    fighter.getINFO();
    mage.getINFO();
};
void Party::heal(std::string name, int num){
    if(name=="all"){
        for(Character* c:{&warrior, &fighter, &mage}){
            c->heal(num);
        }
    }else{
        for(Character* c:{&warrior, &fighter, &mage}){
            if(name==c->getName()){
                c->heal(num);
                return;
            }
        }
        std::cout<<"Invalid input"<<std::endl;
    }
};
void Party::hurt(std::string name, int num){
    if(name=="all"){
        for(Character* c:{&warrior, &fighter, &mage}){
            c->hurt(num);
        }
    }else{
        for(Character* c:{&warrior, &fighter, &mage}){
            if(name==c->getName()){
                c->hurt(num);
                return;
            }
        }
        std::cout<<"Invalid input."<<std::endl;
    }
};
void Party::recover(std::string name, int num){
    if(name=="all"){
        for(Character* c:{&warrior, &fighter, &mage}){
            c->recover(num);
        }
    }else{
        for(Character* c:{&warrior, &fighter, &mage}){
            if(name==c->getName()){
                c->recover(num);
                return;
            }
        }
        std::cout<<"Invalid input"<<std::endl;
    }
};
void Party::cast(std::string name, int num){
    if(name=="all"){
        for(Character* c:{&warrior, &fighter, &mage}){
            c->cast(num);
        }
    }else{
        for(Character* c:{&warrior, &fighter, &mage}){
            if(name==c->getName()){
                c->cast(num);
                return;
            }
        }
        std::cout<<"Invalid input"<<std::endl;
    }
};


void Party::attack(){
    for(Character* c:{&warrior, &fighter, &mage}){
        c->attack();
    }
}