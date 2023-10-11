#pragma once
#include <string>

#define MAX 28

enum Bloodgroup {
  Apos,
  Aneg,
  Bpos,
  Bneg,
  Abpos,
  Abneg,
  Opos,
  Oneg,
};

enum Type {
  Donor,
  Reciever,
};

class Patient {
public:
  std::string name;
  std::string gender;
  int age;
  Bloodgroup group;
  Type type;
};

Bloodgroup get_blood_group_enum(int group);
const char *get_blood_group(Bloodgroup bl);
const char* get_patient_type(Type type);
Type get_patient_type_enum(int type);
void writedb(Patient pats[], int n);
int readdb(Patient pats[]);
