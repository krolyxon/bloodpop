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

  void set(std::string name, std::string gender, int age, Bloodgroup group,
           Type type);
};

// Returns the enum of type Bloodgroup depending on the integer you provide
Bloodgroup get_blood_group_enum(int group);

// Returns string of Bloodgroup enum you provide
const char *get_blood_group(Bloodgroup bl);

// Returns string of Type enum you provide
const char *get_patient_type(Type type);

// Returns the int value of the Bloodgroup enum you provide
int get_blood_group_int(Bloodgroup bl);

// Returns the enum of type Type depending on the integer you provide
Type get_patient_type_enum(int type);

// Writes the array of "Patient"s to the database
void writedb(Patient pats[], int n);

// Reads the database
int readdb(Patient pats[]);

// Deletes the patient from the database
void delete_patient(Patient patient);
