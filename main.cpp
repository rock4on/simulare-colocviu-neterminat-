#include <iostream>
#include <string>
#include <sstream>
using namespace std;
class candidat {
private:
	float cod;
	string optiune;
	bool fac_2 = false;
	string nume;
	bool pasaport;
	float medie_bac;
	float nota_initiala;
	float nota_evaluare;
public:

	// pachet="cod$nume$prenume$fac_2$optiune$"
	// optiune = ID  pachet="pasaport$cod$nume-prenume$fac_2$ID$nota_mate||nota_absolvire$nota_evaluare"
	// optiune = IF  pachet="cod$nume-prenume$fac_2$IF$nota_bac||nota_absolvire$nota_evaluare"
	candidat(string pachet)
	{
		for (int i = 0; i < pachet.length() - 1; i++) if (pachet[i] == '$') pachet[i] = ' ';
		stringstream ss;

		ss << pachet;
		ss >> pasaport;
		ss >> nume;
		ss >> fac_2;
		ss >> optiune;
		ss >> nota_initiala;
		ss >> nota_evaluare;
		// 
		ss >> cod;
	}

	bool pas()
	{
		return pasaport;
	}

	candidat()
	{

	}

	void afisare()
	{
		cout << "[" << endl;
		cout << cod << ",";
		cout << nume << ",";
		cout << fac_2 << ",";
		cout << optiune << ",";
		cout << nota_initiala << ",";
		cout << nota_evaluare << ",";
		cout << "]" << endl;
	}






	float calculare_medie()
	{
		if (fac_2)
		{
			return 0.6 * nota_evaluare + 0.4 * nota_initiala;
		}
		else if (optiune == "ID")
		{
			return 0.6 * nota_evaluare + 0.4 * nota_initiala;
		}
		else if (optiune == "IF")
		{
			return 0.8 * nota_evaluare + 0.2 * nota_initiala;
		}
		return -1;
	}



	string gen_legitimatie()
	{
		if (optiune == "IF")
		{
			stringstream s;
			s << "IF_" << cod;
			string st;
			s >> st;
			return st;
		}
		else if (optiune == "ID")
		{
			stringstream s;
			s << "ID_" << cod;
			string st;
			s >> st;
			return st;
		}
		else return "eroare";
	}


};

// optiune = IF  pachet="cod$nume-prenume$fac_2$IF$nota_bac||nota_absolvire$nota_evaluare"

class facultate {
private:
	// vector pt medile sortate , nu am mai avut timp 
	int nr_locuri_if=0;
	int nr_locuri_id = 0;
	int id_if=0;
	int id_id=0;
	candidat** If;
	candidat** Id;
	int size = 5;
	candidat** pasaport;
	int i_pas=0;
public:
	facultate(int nr_id,int nr_if,int arsize=100)
	{
		size = arsize;
		nr_locuri_id = nr_id;
		nr_locuri_if = nr_if;
		If = new candidat*[size];
		Id = new candidat*[size];
		pasaport = new candidat * [size];
	}

	void af_tot()
	{
		for (int i = 0; i < id_if; i++)
		{
			If[i]->afisare();
		}
		for (int i = 0; i < id_id; i++)
		{
			Id[i]->afisare();
		}
	}

	void add(string tip, string pachet)
	{
		stringstream ss;
		if (tip == "IF") {
			ss << id_if;
			string s;
			ss >> s;
			pachet = pachet + "$" + s;
			If[id_if++] = new candidat(pachet);
			if (If[id_if - 1]->pas()) pasaport[i_pas++] = If[id_if - 1]; 
			return; 
		}
		if (tip == "ID") {
			ss << id_id;
			string s;
			ss >> s;
			pachet + "$" + s;
			Id[id_id++] = new candidat();
			if (Id[id_id - 1]->pas()) pasaport[i_pas++] = Id[id_id - 1];
		}
		
		return;
	}

	void af_pas()
	{
		for (int i = 0; i < i_pas; i++)
			pasaport[i]->afisare();
	}



};




int main()
{
	candidat c("1$Marian$1$IF$10$3");
	facultate f(2,3,10);
	bool ok = 1;
	int opt;




	while (ok)
	{
    
		cout << "1-add,2-af_tot,0-iesire,3-pasaport\n";
		cout << "pachet = \"pasaport(bool)$nume-prenume$fac_2(bool)$IF$nota_bac||nota_absolvire$nota_evaluare\"\n";
		cin >> opt;
		if (opt == 1) { string o1, o2; cin >> o1; cin.clear(); cin >> o2; f.add(o1, o2); }
		if (opt == 0) { ok = 0; }
		if (opt == 2) { f.af_tot(); }
		if (opt == 3) { f.af_pas(); }
	}

	 cout << c.gen_legitimatie();
}
