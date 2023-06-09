#include "cell.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;


cell::cell(char c, int x, int y){
    this->type = c;
    this->baseType = c;
    this->x = x;
    this->y = y;

    if(c == 'A' || '#'){
        this->isHazard = true;
    } else if(c == 'B' || 'S'){
        this->hasWeapon = true;
    }
}

  char cell::display(){
    return type;
  }
  //wumpus enters location 
  void cell::enter(char who, character* c){
    c->current_x = this->getX();
    c->current_y = this->getY();
    this->baseType = type;
    this->type=who;
  }
  // player enters the location
   int cell::enter(char who,player* c){
    c->current_x = this->getX();
    c->current_y = this->getY();

    if(this->type=='>'||this->type=='<'||this->type=='^'||this->type=='v'){
      this->type=who;
      return triggerArrow(this->baseType,c);
    }else if(this->type=='#'){
      cout<<"You hit a snare trap, you lose your turn, but destroy the trap"<<endl;
      this->type=who;
      this->baseType = '.';
      return 0;
    }else if(this->type=='B'){
      cout<<"You find a chest with a Bomb in it, use it carefully"<<endl;
      c->numBomb++;
      this->type=who;
      this->baseType='.';
    }else if(this->type=='S'){
      srand (time(NULL));
      int type = rand()%2;
      if(type==1){
        cout<<"You find a chest with a flimsy sheild in it, this should be good to block any projectiles"<<endl;
        if(!c->hasTrapSheild){
          c->hasTrapSheild=true;
          this->type=who;
          this->baseType='.';
        }else{
        cout<<"You already have one of these sheilds, it dissolves in your hand, never to be seen again."<<endl;
        this->baseType = '.';
        }
      }else{
        cout<<"You find a chest with a sturdy sheild in it, this should be good to block atacks form the wumpus"<<endl;
        if(!c->hasWumpSheild){
          c->hasWumpSheild=true;
          this->type=who;
          this->baseType='.';
        }else{
        cout<<"You already have one of these sheilds, it dissolves in your hand, never to be seen again."<<endl;
        this->baseType = '.';
        }
      }
    
    }
    this->type=who;
    return 1;
  }
  // character leaves location
  void cell::vacate(){
    this->type=baseType;
  }
  int cell::getX(){
    return this-> x;
  }
  int cell::getY(){
    return this-> y;
  }
  //trigger for the arrow trap 
  // return 1=you survive the trap
  // return -1= you DIE
  int cell::triggerArrow(char direction,player* c){
    cout<<"you reach an arrow trap.Pick a direction to defend in a direction"<<endl;
    cout<<"Action: N)orth, S)outh, E)ast, W)est"<<endl;
    char input;
    cin>>input;
    if(direction=='<'&&(input=='W'||input=='w')){
      cout<<"you succesfully defended"<<endl;
      return 1;
    }else if(direction=='^'&&(input=='N'||input=='n')){
      cout<<"you succesfully defended"<<endl;
      return 1;
    }else if(direction=='>'&&(input=='E'||input=='e')){
      cout<<"you succesfully defended"<<endl;
      return 1;
    }else if(direction=='v'&&(input=='S'||input=='s')){
      cout<<"you succesfully defended"<<endl;
      return 1;
    }else{
      if(c->hasTrapSheild){
        c->hasTrapSheild=false;
        cout<<"Ouch,you get hit by the arrow trap but live thanks to your sheild"<<endl;
        cout<<"Your sheild gets destroyed"<<endl;
        return 1;
      }else{
        c->isAlive=false;
        cout<<"Ouch, you get hit by the arrow trap (the same arrow trap will always shoot in the same direction)"<<endl;
        return -1;
      }
    }
    return 1;
  };


void cell::setToEmpty(){
    this->type = '.';
    this->baseType = '.';
}

