#include "patient.h"
#include "imgui/imgui.h"
#include <cstdio>
#include <fstream>
#include <ios>
#include <string>
#include <vector>

#define FILENAME_DB "patients.db"

const char *get_blood_group(Bloodgroup bl) {
  switch (bl) {
  case Apos:
    return "A+";
    break;
  case Aneg:
    return "A-";
    break;
  case Bpos:
    return "B+";
    break;
  case Bneg:
    return "B-";
    break;
  case Abpos:
    return "Ab+";
    break;
  case Abneg:
    return "Ab-";
    break;
  case Opos:
    return "O+";
    break;
  case Oneg:
    return "O-";
    break;
  default:
    return "Nil";
    break;
  }
}

Bloodgroup get_blood_group_enum(int group) {
  switch (group) {
  case 1:
    return Apos;
    break;
  case 2:
    return Aneg;
    break;
  case 3:
    return Bpos;
    break;
  case 4:
    return Bneg;
    break;
  case 5:
    return Abpos;
    break;
  case 6:
    return Abneg;
    break;
  case 7:
    return Opos;
    break;
  case 8:
    return Oneg;
    break;
  default:
    return Apos;
    break;
  }
}

int get_blood_group_int(Bloodgroup bl) {
  switch (bl) {
  case Apos:
    return 0;
    break;
  case Aneg:
    return 1;
    break;
  case Bpos:
    return 2;
    break;
  case Bneg:
    return 3;
    break;
  case Abpos:
    return 4;
    break;
  case Abneg:
    return 5;
    break;
  case Opos:
    return 6;
    break;
  case Oneg:
    return 7;
    break;
  default:
    return 8;
    break;
  }
}
Type get_patient_type_enum(int type) {
  switch (type) {
  case 1:
    return Donor;
    break;
  case 2:
    return Reciever;
    break;
  default:
    return Donor;
    break;
  }
}

const char *get_patient_type(Type type) {
  switch (type) {
  case Donor:
    return "Donor";
    break;
  case Reciever:
    return "Reciever";
    break;
  default:
    return "Nil";
    break;
  }
}

// Split each line of the patient database into a vector of std::string
// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
std::vector<std::string> split(std::string s, std::string delim) {
  size_t pos_start = 0, pos_end, delim_len = delim.length();
  std::string token;
  std::vector<std::string> res;

  while ((pos_end = s.find(delim, pos_start)) != std::string::npos) {
    token = s.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    res.push_back(token);
  }
  res.push_back(s.substr(pos_start));
  return res;
}

void writedb(Patient pats[], int n) {
  std::fstream file(FILENAME_DB, std::ios::out);
  if (file.is_open()) {
    for (int i = 0; i <= n; i++) {
      file << pats[i].name << ";" << pats[i].age << ";" << pats[i].gender << ";"
           << pats[i].type << ";" << (pats[i].group) << ";\n";
    }
    file.close();
  }
}

int readdb(Patient pats[]) {
  std::ifstream file(FILENAME_DB, std::ios::in);
  std::string buf;
  int i = 0;
  while (std::getline(file, buf)) {
    std::vector<std::string> buffer = split(buf, ";");
    pats[i].name = buffer.at(0);
    pats[i].age = std::atoi(buffer.at(1).c_str());
    pats[i].gender = buffer.at(2);
    pats[i].type = get_patient_type_enum(std::atoi(buffer.at(3).c_str()));
    pats[i].group = get_blood_group_enum(std::atoi(buffer.at(4).c_str()));
    i++;
  }
  return i;
}

void delete_patient(Patient patient) {
  std::string del_line;
  del_line.append(patient.name);
  del_line.append(";");
  del_line.append(std::to_string(patient.age));
  del_line.append(";");
  del_line.append(patient.gender);
  del_line.append(";");
  del_line.append(std::to_string(patient.type));
  del_line.append(";");
  del_line.append(std::to_string((get_blood_group_int(patient.group))));
  del_line.append(";");
  printf("%s", del_line.c_str());
  std::ifstream file(FILENAME_DB);
  std::string line;
  std::ofstream temp("temp.db");
  while (std::getline(file, line)) {
    if (line != del_line) {
      temp << line << "\n";
    }
  }
  file.close();
  temp.close();
  remove(FILENAME_DB);
  rename("temp.db", FILENAME_DB);
}
