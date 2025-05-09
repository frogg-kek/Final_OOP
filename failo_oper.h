
#ifndef FAILO_OPER_H
#define FAILO_OPER_H

#include "studentas.h"
#include <string>
#include <vector>
#include "vektorius.h"

// Funkcijos failų skaitymui
Vector<Student> nuskaitytiStudentus(const std::string& failoPavadinimas, double& skaitymoLaikas);

// Funkcijos rezultatų išvedimui
void spausdintiRezultatus(const Vector<Student>& studentai);
void rasytiRezultatus(const std::string& failoPavadinimas, const Vector<Student>& studentai);
void pasirinktiIsvestiesBuda(const Vector<Student>& studentai);

#endif