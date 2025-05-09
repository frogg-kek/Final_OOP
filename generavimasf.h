#ifndef FILE_GENERATOR_H
#define FILE_GENERATOR_H

#include <vector>
#include <string>
#include "studentas.h"
#include "vektorius.h"

void generuotiStudentuFailus(const std::vector<int>& kiekiai, std::vector<std::string>& failugen);
void rusiotiStudentusISFailus(const std::string& failoPavadinimas, std::vector<std::string>& failugen);
void rikiuotiStudentusPriesRusiavima(Vector<Student>& studentai);

#endif