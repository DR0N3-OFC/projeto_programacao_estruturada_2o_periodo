#define YEL "\033[1;93m"        //YELLOW       
#define GRE "\033[1;92m"        //GREEN
#define DAR_GRE "\033[1;32m"    //DARK GREEN
#define RED "\033[1;31m"        //RED
#define BLU "\033[1;34m"        //BLUE
#define FUN_BLA "\033[1;40m"    //BLACK BACKGROUND
#define LIG_GRE "\033[1;37m"    //LIGHT GREEN
#define RESET "\033[0;0m"       //DEFAULT COLOR

struct TCarro{
  char dono[50], placa[10], modelo[20], cor[15];
};

void gotoxy(int x, int y);
void limpa();
void titulo(char nome[]);
void intro(char nome[], int *n_carros);
int menu(int n_carros, int patio, int rua);
void add_carro(int n_carros, int *patio, int *rua, struct TCarro vet_patio[], struct TCarro vet_rua[], char nome[]);
void rem_carro(int n_carros, int *patio, int *rua, struct TCarro vet_patio[], struct TCarro vet_rua[]);
void lavagem(struct TCarro vet_patio[], int patio, char nome[]);
void espera(struct TCarro vet_rua[], int rua, char nome[], int patio);
void encerra_programa();
void criaCarro(struct TCarro *carro, char nome[]);
void lavaCarro(struct TCarro vet_patio[], struct TCarro vet_rua[], int *patio, int *rua, int n_carros);