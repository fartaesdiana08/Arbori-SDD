#include<iostream>

using namespace std;

struct Masina{
	int id;
	char* marca;
	int nrKm;
};

Masina creareMasina(int id, const char* marca, int km){
	Masina m;
	m.id = id;
	m.marca = (char*)malloc(sizeof(char) * (strlen(marca) + 1));
	strcpy(m.marca, marca);
	m.nrKm = km;
	return m;
}

void afisareMasina(Masina m) {
	printf("\n Masina cu id-ul %d, marca %s, are nr de km %d", m.id, m.marca, m.nrKm);
}

struct nod {
	Masina info;
	nod* st;
	nod* dr;
};
nod* creareNod(Masina m, nod* st, nod* dr) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = creareMasina(m.id, m.marca, m.nrKm);
	nou->st = st;
	nou->dr = dr;
	return nou;
}
//returneaza adresa de inceput a arborelui;
//la fct recursive nu initializam cu null in functie pt ca se reapeleaza;
nod* inserareABC(nod* root, Masina m) /*unde inseram, de unde*/{
	if (root) {
		//valorile mai mici in stanga, valorile mai mari in dreapta
		if (m.nrKm > root->info.nrKm) {
			root->dr = inserareABC(root->dr, m);
		}
		else if (m.nrKm < root->info.nrKm) {
			root->st = inserareABC(root->st, m);
		}
		return root;
	}
	else {
		nod* nou = creareNod(m, NULL, NULL);
		return nou;
	}
}

void SRD(nod* root) { //inordine
	if (root) {
		SRD(root->st);
		afisareMasina(root->info);
		SRD(root->dr );
	}
}
void RSD(nod* root) { //preordine
	if (root) {
		afisareMasina(root->info);
		RSD(root->st);
		RSD(root->dr);
	}
}
void SDR(nod* root) { //postordine
	if (root) {
		RSD(root->st);
		RSD(root->dr);
		afisareMasina(root->info);
	}
}

//arbore AVL=echilibrat, adica are gr de echilibru -1,0,1
//-2 sau 2, necesita reechilibrare;
//gr de echilibru= inaltime dreapta-inaltime st;
//inaltime: 1+max(Hs, Hd);


//nodul returnat este radacina;
int maxim(int a, int b) {
	return(a > b) ? a : b;
	//daca e mai mare decat b, return a, altfel returneaza b;
}

int inaltime(nod* root) {
	if (root) {
		return 1 + maxim(inaltime(root->st), inaltime(root->dr));
	}
	else {
		return 0;
	}
}

int gradEchilibru(nod* root) {
	return inaltime(root->dr) - inaltime(root->st);
}

nod* rotireStanga(nod * root) {
	nod* aux = root->dr;
	root->dr = aux->st;
	aux->st = root;
	return aux;
}

nod* rotireDreapta(nod* root) {
	nod* aux = root->st;
	root->st = aux->dr;
	aux->dr = root;
	return aux;
}

nod* inserareAVL(nod* root, Masina m) /*unde inseram, de unde*/ {
	if (root) {
		//valorile mai mici in stanga, valorile mai mari in dreapta
		if (m.nrKm > root->info.nrKm) {
			root->dr = inserareAVL(root->dr, m);
		}
		else if (m.nrKm < root->info.nrKm) {
			root->st = inserareAVL(root->st, m);
		}
		//reechilibrarea
		int ge = gradEchilibru(root);
		if (ge == -2) {//dezechilibru stanga
			int ges = gradEchilibru(root->st);
			if (ges == -1) {
				//o singura rotire
				root = rotireDreapta(root);
			}
			else {
				//dubla rotire
				root->st = rotireStanga(root->st);
				root = rotireDreapta(root);
			}
		}
		if (ge == 2) {//dezechilibru pe partea dreapta
			int ged = gradEchilibru(root->dr);
			if (ged == 1) {
				//o sg rotire
				root = rotireStanga(root);

			}
			else {
				//dubla rotire
				root->dr = rotireDreapta(root->dr);
				root = rotireStanga(root);
			}
		}
		return root;
	}
	else {
		nod* nou = creareNod(m, NULL, NULL);
		return nou;
	}
}

void main() {
	nod* root = NULL;
	root = inserareABC(root, creareMasina(1, "Mhjbc", 100));
	root = inserareABC(root, creareMasina(2, "fbgn", 90));
	root = inserareABC(root, creareMasina(3, "mnfd", 95));
	root = inserareABC(root, creareMasina(4, "ibwriub", 200));
	root = inserareABC(root, creareMasina(5, "thtb", 250));
	root = inserareABC(root, creareMasina(6, "sfg", 30));
	root = inserareABC(root, creareMasina(7, "yrh", 115));

	SRD(root);

	printf("\n afisare avl \n ");
	nod* avl = NULL;
	avl = inserareAVL(avl, creareMasina(1, "cdjsgc", 100));
	avl = inserareABC(avl, creareMasina(2, "ufgsh", 90));
	avl = inserareABC(avl, creareMasina(3, "fajsgf", 95));
	avl = inserareABC(avl, creareMasina(4, "sdfus", 200));
	avl = inserareABC(avl, creareMasina(5, "dsfhg", 300));
	avl = inserareABC(avl, creareMasina(6, "sagfjs", 400));
	avl = inserareABC(avl, creareMasina(7, "hgdsad", 115));
	SRD(avl);
}
