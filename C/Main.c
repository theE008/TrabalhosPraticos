/**
 * @date: 11/2024
 * @author: Thiago Pereira de Oliveira
 * @details: Meu código fonte dos TPs para C, onde guardo a base para as futuras atividades
 * do TP 4.
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////
// BIBLIOTECAS

// apenas para funções que não sei fazer

#include <stdlib.h> // para o malloc
#include <stdio.h> // para o printf
#include <time.h> // para clock

/////////////////////////////////////////////////////////////////////////////////////////////////////
// CONTAR COMPARAÇÕES

// substitui o if para uma versão que conta comparações. Alterações abaixo também, no QOL
#define IF(comp) if(comp && (++comparacoes))
long long int comparacoes = 0.0;

/////////////////////////////////////////////////////////////////////////////////////////////////////
// BOOLEAN & NÚMEROS NATURAIS

typedef unsigned int nat; // numeros naturais

typedef enum { false = 0, true = 1 } boolean;

/////////////////////////////////////////////////////////////////////////////////////////////////////
// QOL

// cria uma linha fácil de ver e remover que printa o número da linha onde está
#define DEBUGLINE_DEBUGLINE_DEBUGLINE_DEBUGLINE_DEBUGLINE \
if (!verde) printf ("\n\tDebug reached line %d\n", __LINE__)

// for simplificado
#define loop(quantas_vezes,var) for(int var = 0; var < quantas_vezes && (++comparacoes); var++)

// else if
#define elif(comp) else if(comp && (++comparacoes))

// usando o null do java
#define null NULL

// println
#define println(...) printf (__VA_ARGS__); printf ("\n");

// guarda o fato de se está no site verde ou não
boolean verde = false;

/////////////////////////////////////////////////////////////////////////////////////////////////////
// CONTROLE DE MEMÓRIA

// coisas ainda não definidas
void colorir (char* text, char* background);
void murder (char* entrada);

// malloc mais simples/seguro/contabilizado
#define reservar(tipo,quantos) (tipo*) reservar_espaco_funcao (quantos*sizeof (tipo)); 

// Free mais seguro/contabilizado
int reservas_feitas = 0; // Para garantir que tudo foi liberado na memória.
int limpezas_feitas = 0;
#define limpar(val) if(val!=null && limpezas_feitas++){free(val); val = null;}

// Malloc mais seguro
void* reservar_espaco_funcao (size_t Size)
{
    void* try = malloc (Size);
    reservas_feitas++;

    IF (try == null) 
        murder ("Erro ao criar espaco");
    else return try;
}

// Avisa o que tá sobrando de lixo na memória
int quantas_chamadas = 0; // para remover o calculo dos IFs dessa função
void status_da_memoria ()
{
    int razao = reservas_feitas - limpezas_feitas;
    int recomparacoes = comparacoes - 19 * quantas_chamadas++;

    IF    (razao ==  0) colorir ("verde"   , "preto");
    elif  (razao <= 10) colorir ("amarelo" , "preto");
    else                colorir ("vermelho", "preto");
    
    IF    (verde ==  0) 
    printf
    (
        "\n\t%s\n\t%s: %d%s\n\t%s: %d%s\n\t%s: %d%s\n\t%s\n\t%s: %d%s\n\t%s\n\n",
        "+---------------------------------------+",
        "|Comparos feitos",recomparacoes, "  \t\t|",
        "|Reservas feitas",reservas_feitas,"\t\t\t|",
        "|Limpezas feitas",limpezas_feitas,"\t\t\t|",
        ">---------------------------------------<",
        "|Lixo de memoria", razao,        "\t\t\t|",
        "+---------------------------------------+"
    );

    colorir ("branco"  , "preto");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// CORE

boolean eh_igual (char* t1, char* t2);

// Texto levemente destacado.
void important (char* entrada)
{
    printf ("\n\n\t%s\n\n", entrada);
}

// Texto mais levemente destacado.
void less_important (char* entrada)
{
    printf ("\t%s\n", entrada);
}

/**
 * Modifica a cor do terminal
 * 
 * Texto Only:
 * negrito
 * sublinhado
 * 
 * Ambos:
 * preto
 * vermelho
 * verde
 * amarelo
 * azul
 * magenta
 * ciano
 * branco
 */
void colorir (char* text, char* background)
{
    int texto = 37;
    int fundo = 40;

    IF   (eh_igual (text, "negrito"     )) texto =  1;
    elif (eh_igual (text, "sublinhado"  )) texto =  4;
    elif (eh_igual (text, "preto"       )) texto = 30;
    elif (eh_igual (text, "vermelho"    )) texto = 31;
    elif (eh_igual (text, "verde"       )) texto = 32;
    elif (eh_igual (text, "amarelo"     )) texto = 33;
    elif (eh_igual (text, "azul"        )) texto = 34;
    elif (eh_igual (text, "magenta"     )) texto = 35;
    elif (eh_igual (text, "ciano"       )) texto = 36;
    elif (eh_igual (text, "branco"      )) texto = 37;

    IF   (eh_igual (background, "preto"         )) fundo = 40;
    elif (eh_igual (background, "vermelho"      )) fundo = 41;
    elif (eh_igual (background, "verde"         )) fundo = 42;
    elif (eh_igual (background, "amarelo"       )) fundo = 43;
    elif (eh_igual (background, "azul"          )) fundo = 44;
    elif (eh_igual (background, "magenta"       )) fundo = 45;
    elif (eh_igual (background, "ciano"         )) fundo = 46;
    elif (eh_igual (background, "branco"        )) fundo = 47;

    printf ("\033[%d;%dm",texto, fundo);
}

// Mensagem colorida
void mensagem_colorida (char* mensagem, char* cor, boolean importante)
{
    colorir (cor, "preto");
    IF (importante) important (mensagem);
    else less_important (mensagem);
    colorir ("branco", "preto");
}

// Mensagem de erro
void murder (char* entrada)
{
    mensagem_colorida (entrada, "vermelho", true);

    exit (-1);
}

// Informação, não aparece se enviado no verde
void informar (char* entrada, char* cor, boolean importante)
{
    IF (!verde) mensagem_colorida (entrada, cor, importante);
}

// calloc
char* reservar_string (size_t quantos)
{
    IF (quantos <= 0) murder ("Alocando memoria nula");
    char* tmp = (char*) reservar_espaco_funcao (quantos);

    loop (quantos, x) tmp [x] = '*';

    return tmp;
}

// nextLine
char* proxima_linha (FILE* arquivo)
{
    char *saida = reservar (char, 500);
    IF (arquivo != null)
    {
        IF (fscanf (arquivo, "%[^\n]\n", saida) != 1)
        {murder ("Arquivo lido alem da conta");}
    }
    else   
    IF (scanf ("%[^\n]\n", saida) != 1)
        {murder ("Input incorreto do usuario");}

    return saida;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// MATEMÁTICA

// potencia simples de numero inteiro
int potencia (int a, int b)
{
    int resp = 1;
    loop (b, x) resp *= a;

    return resp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// TEXTOS

// Retorna a quantia de caracteres presente em uma string.
int tamanho (char* entrada)
{
    IF (entrada == null) murder ("Impossivel pegar tamanho de string inexistente");
    else
    {
        int resposta = 0;

        while (entrada [resposta] != '\0') resposta++;

        return resposta;
    }
}

// Testa se duas strings são iguais
boolean eh_igual (char* t1, char* t2)
{
    int tam1 = tamanho (t1);
    boolean resposta = true;

    IF (tam1 != tamanho (t2)) resposta = false;
    else
    {
        for (int x = 0; x < tam1 && resposta; x++)
            IF (t1 [x] != t2 [x]) resposta = false;
    }

    return resposta;
}

// Compara duas strings
int comparar (char* t1, char* t2)
{
    int resposta = 0;
    int tam1 = tamanho (t1);
    int tam2 = tamanho (t2);
    int tam  = (tam1 > tam2)?tam2:tam1;

    for (int x = 0; x <= tam && !resposta; x++) resposta = t2 [x] - t1 [x];

    return resposta;
}

// Strcpy. Retorna o tamanho da string (em caracteres) final.
int copiar_texto (char* t1, char* t2)
{
    int x = 0;

    IF (tamanho (t1) >= tamanho (t2))
    {
        char c = '*';

        while (c != '\0')
        {
            c = t2 [x];
            t1 [x] = c;

            x++;
        }
    }
    else
        murder ("Uma tentativa de copiar um texto para uma string menor foi feita!");

    return x - 1;
}

// Quantas vezes um caractere em específico aparece na string
int contar_um_caractere (char* texto, char carac)
{
    IF (texto == null) murder ("Texto inexistente em contar um caractere");
    else
    {
        int tam = tamanho (texto);
        int resposta = 0;

        loop (tam, x) IF (texto [x] == carac) resposta++;

        return resposta;
    }
}

// Split para C
char** separar (char* texto, char carac, int *saida_de_quantos)
{
    IF (texto == null) murder ("Texto inexistente em separar");
    else
    {
        int quantos = contar_um_caractere (texto, carac) + 1;
        int tam     = tamanho (texto);
        int index   = 0;
        int y       = 0;

        char** resposta = reservar (char*, quantos);

        loop (quantos, x)
        {
            resposta [x] = reservar_string (tam + 1);
        }

        loop (tam, x)
        {
            IF (texto [x] == carac)
            {
                resposta [index][y] = '\0';
                index++;
                y = 0;
            }
            else
            {
                resposta [index][y++] = texto [x];
            }
        }

        resposta [index][y] = '\0';

        IF (saida_de_quantos != null) *saida_de_quantos = quantos; 
        return resposta;
    }
}

void imprimir_partes (char* texto, char separador)
{
    int x = 0;
    char** saida = separar (texto, separador, &x);

    loop (x, y)
    {
        printf ("[%d] (size %3d) %s\n", y + 1, tamanho (saida [y]), saida [y]);
    }

    println (null);
}

// parseInt de 1 caractere
unsigned short int char_para_Int (char carac)
{
    IF ('0' <= carac && carac <= '9')
    {
        return carac - '0';
    }
    else
        murder ("Caractere nao numerico nao pode virar numero");
}

// parseInt
int Str_para_Int (char* str)
{
    IF (str == null) murder ("Texto inexistente em Str_para_Int");
    else
    {
        int tam = tamanho (str);
        int resposta = 0;
        int base = potencia (10, tam - 1);

        loop (tam, x) 
        {
            resposta += base * char_para_Int (str [x]);
            base /= 10;
        }

        return resposta;
    }
}

// recebe um digito e o tranforma em char
char Int_para_char (short unsigned int val)
{
    IF (val > 9) murder ("Valor muito grande");
    else
    return '0' + val;
}

// conversão para evitar erros
char* char_para_Str (char in)
{
    char* out = reservar_string (2);
    out [0] =   in;
    out [1] = '\0';

    return out;
}

// recebe uma string e a transforma em double
double Str_para_Dbl (char* str)
{
    IF (str == null) murder ("Texto inexistente em Str_para_Dbl");
    else
    {
        int quantas = 0;
        char** partes = separar (str, '.', &quantas);
        double resposta = 0;

        // casas depois da virgula;
        int casas = tamanho (partes [1]);

        resposta  = Str_para_Int (partes [0]);
        double p2 = Str_para_Int (partes [1]);

        resposta += p2 / (double) potencia (10, casas);

        IF (partes != null && quantas == 2 && partes [0] != null && partes [1] != null)
        {
            loop (quantas, x)
            {
                limpar (partes [x]);
            }
            //limpar (partes); // <<<< adicionar essa linha dá um erro em judas perdeu as botas no código
            // não entendi porque, não acho que a eficiência que isso me daria vale realmente a pena 
            // o sofrimento mental que passei por isto, então estou aposentando essa por enquanto.

            limpezas_feitas++; // <- APENAS PARA SABER QUANTO EU GANHARIA COM ISSO, NÃO TEM UMA LIMPEZA AQUI AINDA!

            // 2400 lixo de memoria -> 880
        }
        else murder ("Algo de errado aconteceu em str para dbl");

        return resposta;
    }
}

// verifica se a string tem um caractere em especifico
boolean contem_caractere (char* entrada, char carac)
{
    IF (entrada == null) murder ("Entrada invalida em contem caractere");
    else
    {
        int tam = tamanho (entrada);
        boolean resposta = false;

        for (int x = 0; x < tam && !resposta; x++) 
            IF (entrada [x] == carac)
                resposta = true;
        
        return resposta;
    }
}

// remove espaços do inicio e do final se existirem
char* trim (char* entrada)
{
    IF (entrada == null) murder ("Trim com entrada invalida");
    else
    {
        int tam = tamanho (entrada);
        char* saida = reservar_string (tam + 1);
        int y = 0;

        loop ((tam - 1), x)
        {
            IF (x == 0)
            {
                IF (entrada [0] != ' ')
                saida [y++] = entrada [x];
            }
            else
            saida [y++] = entrada [x];
        }

        IF (entrada [tam - 1] == ' ')
        saida [y] = '\0';
        else
        {
            saida [y] = entrada [tam - 1];
            saida [y + 1] = '\0';
        }

        return saida;
    }
}

// Remove os caracteres presentes na segunda string de dentro da primeira e retorna
char* remover_caracteres (char* texto, char* remocoes)
{
    IF (texto == null || remocoes == null) murder ("Entradas invalidas em remover caracteres");
    else
    {
        int tam = tamanho (texto);
        char* resposta = reservar_string (tam);
        int index = 0;

        loop (tam, x)
        {
            IF (!contem_caractere (remocoes, texto [x]))
            {
                resposta [index++] = texto [x];
            }
        }

        resposta [index] = '\0';

        return resposta;
    }
}

// Concatenar
char* concatenar (char* t1, char* t2)
{
    IF (t1 == null || t2 == null) murder ("Texto inexistente em concatenar");
    else
    {
        int tam1 = tamanho (t1);
        int tam2 = tamanho (t2);

        int tamfinal = tam1 + tam2 + 1;
        char* tmp = reservar_string (tamfinal);

        copiar_texto (tmp, t1);

        for (int x = tam1; x < tamfinal; x++)
        {
            tmp [x] = t2 [x - tam1];
        }

        tmp [tamfinal] = '\0';

        return tmp;
    }
}
char* conc_3 (char* t1, char* t2, char* t3)
{
    char* a = concatenar (t1, t2);
    char* b = concatenar (a, t3);

    limpar (a);

    return b;
}
char* conc_4 (char* t1, char* t2, char* t3, char* t4)
{
    char* a = conc_3 (t1, t2, t3);
    char* b = concatenar (a, t4);

    limpar (a);

    return b;
}
char* conc_5 (char* t1, char* t2, char* t3, char* t4, char* t5)
{
    char* a = conc_4 (t1, t2, t3, t4);
    char* b = concatenar (a, t5);

    limpar (a);

    return b;
}

// recebe um numero e o transforma em string
char* Int_para_Str (int val)
{
    char* resposta;

    IF (val != 0)  
    {
        char* esquerda = Int_para_Str (val/10);
        char* digito_f = char_para_Str (Int_para_char (val % 10));

        resposta = concatenar (esquerda, digito_f);

        limpar (esquerda);
        limpar (digito_f);
    }
    else
    {
        resposta = reservar_string (1);
        resposta [0] = '\0';
    }

    return resposta;
}

// insere caracteres no inicio se o tamanho nao for o correto
char* garantir_tamanho (char* entrada, int tam, char carac)
{
    IF (entrada == null) murder ("Entrada indefinida em garantir tamanho");
    else
    {
        int tama = tamanho (entrada);
        char* resposta;

        IF (tam > tama)
        {
            resposta = reservar_string (tam - tama);

            loop ((tam - tama), x)
            {
                resposta [x] = carac;
            }
        }
        else
        {
            resposta = "";
        }

        return concatenar (resposta, entrada);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// STRING

// tipo de dado String
typedef struct String
{
    char* texto;
    int tamanho;
}
String;
typedef String* ptr_String;
void free_String (ptr_String str); 

// construtor (duas reservas)
ptr_String novo_String (char* entrada)
{
    ptr_String tmp = reservar (String, 1);

    IF (entrada == null)
    {
        tmp->texto = reservar (char, 1);
        tmp->tamanho = 0;
    }
    else
    {
        int tam = tamanho (entrada);
        tmp->tamanho = tam;
        tmp->texto = reservar_string (tam + 1);

        copiar_texto (tmp->texto, entrada);
    }

    return tmp;
}

// alterar
void alterar_String (ptr_String *str, char* texto)
{
    IF (str == null || texto == null)
        murder ("Valor inexistente em alterar String");
    {
        free_String (*str);
        *str = novo_String (texto);
    }
}

// destrutor
void free_String (ptr_String str)
{
    IF (str != null)
    {
        boolean gambito = (str->texto != null); // sacrifico uma comparação em troca do funcionamento
        
        if (gambito) limpar (str->texto);
        
        if (gambito) limpar (str);
        
    }
    else
        murder ("String sendo deletado nao existe");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// LISTA DE STRING ESTÁTICA

// definindo a lista
typedef struct Lista_de_String_Estatica
{
    String **lista;
    int          x;
    int    tamanho;
}
Lista_de_String_Estatica;
typedef Lista_de_String_Estatica* ptr_Lista_de_String_Estatica;

// construtor (2 reservas + string*tamanho reservas) = 2 + 2*tam res
ptr_Lista_de_String_Estatica novo_LdSe (int tamanho)
{
    ptr_Lista_de_String_Estatica tmp = reservar (Lista_de_String_Estatica, 1);

    tmp->tamanho = tamanho;
    tmp->x = 0;

    tmp->lista = reservar (ptr_String, tamanho);

    loop (tamanho, x)
    {
        tmp->lista [x] = novo_String (null);
    }

    return tmp;
}

// adicionar
void adicionar_na_LdSe (ptr_Lista_de_String_Estatica lista, ptr_String valor)
{
    IF (lista == null || valor == null) murder ("Valor inexistente em adicionar na LDSE");
        elif (lista->x >= lista->tamanho) murder ("LdSe muito pequena");
            else
            {
                free_String (lista->lista [lista->x]); // reduziu a produção de lixo para 34k
                lista->lista [lista->x++] = valor;
            }
}

// imprime todos os elementos
void imprimir_LdSe (ptr_Lista_de_String_Estatica lista)
{
    IF (lista == null) murder ("Lista inexistente em impressao");

    loop (lista->x, x)
    {
        println ("[%d] (tam %d) %s", x, lista->lista [x]->tamanho, lista->lista [x]->texto);
    }

    println (null);
}

// destrutor
void free_LdSe (ptr_Lista_de_String_Estatica lista)
{
    IF (lista != null)
    {
        loop (lista->tamanho, x)
        {
            free_String (lista->lista [x]);
        }

        limpar (lista->lista);
        
        limpar (lista);
    }
    else
        murder ("Lista sendo deletada nao existe");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// DATA

// tipo de dado Data
typedef struct Data
{
    int dia;
    int mes;
    int ano;
}
Data;
typedef Data* ptr_Data;

// construtor
ptr_Data novo_Data (char* texto)
{
    ptr_Data tmp = reservar (Data, 1);
    tmp->dia = 0;
    tmp->mes = 0;
    tmp->ano = 0;

    IF (texto != null)
    {
        char** cut = separar (texto, '/', null);

        tmp->dia = Str_para_Int (cut [0]);
        tmp->mes = Str_para_Int (cut [1]);
        tmp->ano = Str_para_Int (cut [2]);

        limpar (cut [0]); // reduziu a produção de lixo para 31k 
        limpar (cut [1]);
        limpar (cut [2]);
        limpar (cut    );
    }

    return tmp;
}

// converte data para String
char* Data_para_Str (ptr_Data data)
{
    char* diastr = Int_para_Str (data->dia);
    char* messtr = Int_para_Str (data->mes);
    char* anostr = Int_para_Str (data->ano);

    char* diagrt = garantir_tamanho (diastr, 2, '0');
    char* mesgrt = garantir_tamanho (messtr, 2, '0');
    char* anogrt = garantir_tamanho (anostr, 4, '0');

    char* resposta = conc_5 (diagrt, "/", mesgrt, "/", anogrt);

    limpar (diastr);
    limpar (messtr);
    limpar (anostr);

    limpar (diagrt);
    limpar (mesgrt);
    limpar (anogrt);

    return resposta;
}

// destrutor
void free_Data (ptr_Data data)
{
    IF (data != null)
    {
        limpar (data);
    }
    else
        murder ("Data sendo deletada nao existe");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// POKEMON

// tipo de dado Pokemon
typedef struct Pokemon
{
    int Id;
    int geracao;
    ptr_String nome;
    ptr_String descricao;
    ptr_Lista_de_String_Estatica tipos;
    ptr_Lista_de_String_Estatica habilidades;
    double peso;
    double tamanho;
    int razao_de_captura;
    boolean eh_lendario;
    ptr_Data Data_de_captura;
}
Pokemon;
typedef Pokemon* ptr_Pokemon;

// construtor
ptr_Pokemon novo_Pokemon ()
{
    ptr_Pokemon tmp = reservar (Pokemon, 1);

    tmp->Id = 0;
    tmp->geracao = 0;
    tmp->nome = novo_String (null);
    tmp->descricao = novo_String (null);
    tmp->tipos = novo_LdSe (2);
    tmp->habilidades = novo_LdSe (1);
    tmp->peso = 0.0;
    tmp->tamanho = 0.0;
    tmp->razao_de_captura = 0;
    tmp->eh_lendario = false;
    tmp->Data_de_captura = novo_Data (null);

    return tmp;
}

// ler
void ler_Pokemon (ptr_Pokemon poke, char* texto)
{
    int quantas_partes = 0;
    char ** corte = separar (texto, '"', &quantas_partes);

    // --- parte antes de habilidades (corte [0])
    int quantos_corte_0 = 0;

    int tam = tamanho (corte [0]);
    corte [0] [tam - 1] = '\0';
    IF (corte [0] [tam - 2] == ',')
    corte [0] [tam - 2] = '\0';

    char ** corte_0 = separar (corte [0], ',', &quantos_corte_0);
    
    // Id
    poke->Id = Str_para_Int (corte_0 [0]);

    // Geração
    poke->geracao = Str_para_Int (corte_0 [1]); 

    // Nome
    alterar_String (&poke->nome, corte_0 [2]);

    // Descrição
    alterar_String (&poke->descricao, corte_0 [3]);

    // Tipos
    adicionar_na_LdSe (poke->tipos, novo_String (corte_0 [4]));
    IF (quantos_corte_0 == 6) 
    adicionar_na_LdSe (poke->tipos, novo_String (corte_0 [5]));

    // --- habilidades (corte [1])
    int quantos_corte_1 = 0;

    char* removidos = remover_caracteres (corte [1], "[]'");
    char ** corte_1 = separar (removidos, ',', &quantos_corte_1);

    free_LdSe (poke->habilidades);
    poke->habilidades = novo_LdSe (quantos_corte_1);

    loop (quantos_corte_1, x)
    {
        char* aparado = trim (corte_1 [x]);
        adicionar_na_LdSe (poke->habilidades, novo_String (aparado));

        limpar (aparado); //8k -> 6k
    }

    // --- outros (corte [2])
    int quantos_corte_2 = 0;
    corte [2] [0] = ' ';

    char* aparado = trim (corte [2]);
    char ** corte_2 = separar (aparado, ',', &quantos_corte_2);

    // Peso
    IF (tamanho (corte_2 [0])) poke->peso = Str_para_Dbl (corte_2 [0]);

    // Tamanho
    IF (tamanho (corte_2 [1])) poke->tamanho = Str_para_Dbl (corte_2 [1]);

    // Razão
    poke->razao_de_captura = Str_para_Int (corte_2 [2]);

    // É lendário
    poke->eh_lendario = Str_para_Int (corte_2 [3]);

    // Data
    free_Data (poke->Data_de_captura);
    poke->Data_de_captura = novo_Data (corte_2 [4]);

    // liberação (isso vai demorar)
    loop (quantas_partes, x)
    {
        limpar (corte [x]); // 25k de lixo -> 21k de lixo
    }
    limpar (corte);

    loop (quantos_corte_0, x)
    {
        limpar (corte_0 [x]); // 21k de lixo -> 16k de lixo
    }
    limpar (corte_0);

    loop (quantos_corte_1, x)
    {
        limpar (corte_1 [x]); // 21k de lixo -> 16k de lixo
    }
    limpar (corte_1);

    loop (quantos_corte_2, x)
    {
        limpar (corte_2 [x]); // 16k de lixo -> 9k de lixo! (diminuiu exponencialmente, no inicio era 44k)
    }
    limpar (corte_2);

    limpar (removidos); // 9k -> 8k
    limpar (aparado); // 6k -> 5k
}

// destrutor
void free_Pokemon (ptr_Pokemon poke)
{
    IF (poke == null) murder ("Pokemon sendo deletado nao existe");
    else
    {
        free_String (poke->nome);
        free_String (poke->descricao);
        free_LdSe   (poke->tipos);
        free_LdSe   (poke->habilidades);
        free_Data   (poke->Data_de_captura);
        
        limpar (poke);
    }   
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/// GERENCIADOR

// tipo de dado Gerenciador
typedef struct Gerenciador
{
    clock_t tempo_inicial;
    int quantos_pokemons;
    Pokemon **pokemons;
}
Gerenciador;
typedef Gerenciador* ptr_Gerenciador;

// construtor 
ptr_Gerenciador novo_Gerenciador ()
{
    ptr_Gerenciador tmp = reservar (Gerenciador, 1);
    tmp->tempo_inicial = clock (); 
    int quantos_pokemons = 801;

    FILE* arquivo = fopen ("../pokemon.csv", "rt");

    IF (arquivo == null)
    {
        arquivo = fopen ("/tmp/pokemon.csv", "rt");

        IF (arquivo == null) murder ("Arquivo CSV inexistente.");

        verde = true;
    }

    tmp->pokemons = reservar (ptr_Pokemon, quantos_pokemons);
    tmp->quantos_pokemons = quantos_pokemons;

    char* lixo = proxima_linha (arquivo); limpar (lixo);

    loop (quantos_pokemons, x)
    {
        tmp->pokemons [x] = novo_Pokemon ();

        char* linha = proxima_linha (arquivo);
        ler_Pokemon (tmp->pokemons [x], linha);

        limpar (linha); // 879 alocações lixo de memória -> 77 alocações lixo de memória
    }

    fclose (arquivo);
    return tmp;
}

// todos os nomes
void imprimir_nomes_Gerenciador (ptr_Gerenciador gere)
{
    int quantos = gere->quantos_pokemons;

    loop (quantos, x)
    {
        printf ("%s\n", gere->pokemons [x]->nome->texto);
    }
}

// todos os tipos
void imprimir_tipos_Gerenciador (ptr_Gerenciador gere)
{
    int quantos = gere->quantos_pokemons;

    loop (quantos, x)
    {
        println ("ID %d", x + 1);
        imprimir_LdSe (gere->pokemons [x]->tipos);
    }
}

// todas as habilidades
void imprimir_habilidades_Gerenciador (ptr_Gerenciador gere)
{
    int quantos = gere->quantos_pokemons;

    loop (quantos, x)
    {
        println ("ID %d", x + 1);
        imprimir_LdSe (gere->pokemons [x]->habilidades);
    }
}

// todos tamanhos
void imprimir_tamanhos_Gerenciador (ptr_Gerenciador gere)
{
    int quantos = gere->quantos_pokemons;

    loop (quantos, x)
    {
        println ("ID %d", x + 1);
        println ("%lf", gere->pokemons [x]->tamanho);
    }
}

// todas datas
void imprimir_datas_Gerenciador (ptr_Gerenciador gere)
{
    int quantos = gere->quantos_pokemons;

    loop (quantos, x)
    {
        println ("ID %d", x + 1);
        char* ptr = Data_para_Str (gere->pokemons [x]->Data_de_captura);
        println ("%s", ptr);
        limpar (ptr);
    }
}

// destrutor
void free_Gerenciador (ptr_Gerenciador gere)
{
    IF (gere == null) murder ("Gerenciador sendo deletado nao existe");
    else
    {
        loop (gere->quantos_pokemons, x)
            free_Pokemon (gere->pokemons [x]);

        limpar (gere->pokemons);

        double tempo_total = ((double) (clock () - gere->tempo_inicial))/CLOCKS_PER_SEC;

        FILE* arquivo = fopen ("Matricula.txt", "wt");

        fprintf (arquivo, "Matricula: 835251 \tTempo de execucao (em ms): %lf\tComparacoes: %d", tempo_total, comparacoes);

        fclose (arquivo);
        limpar (gere);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// CÉLULA DUPLA STRING

// Tipo de dado da célula duplamente encadeada. Tanto para listas quanto para árvores
typedef struct CelulaDuplaStr CelulaDuplaStr;
typedef CelulaDuplaStr* ptr_CelulaDuplaStr;
struct CelulaDuplaStr
{
    ptr_CelulaDuplaStr esq;
    ptr_CelulaDuplaStr dir;
    ptr_String valor;

    int quantidade; // aparicoes do valor na estrutura
};

// construtor
ptr_CelulaDuplaStr novo_CelulaDuplaStr (ptr_String valor)
{
    ptr_CelulaDuplaStr tmp = reservar (CelulaDuplaStr, 1);

    tmp->esq = null;
    tmp->dir = null;
    tmp->valor = valor;
    tmp->quantidade = 1;

    return tmp;
}

// destrutor
void free_CelulaDuplaStr (ptr_CelulaDuplaStr cel)
{
    IF (cel == null) murder ("CelulaDuplastr sendo deletado nao existe");
    else
    {
        free_String (cel->valor);

        limpar (cel);
    }
}

// destrutor completo do tipo de dado
void freeAll_CelulaDuplaStr (ptr_CelulaDuplaStr cel)
{
    IF (cel != null)
    {
        
        freeAll_CelulaDuplaStr (cel->esq);
        
        freeAll_CelulaDuplaStr (cel->dir);
        
        if (cel->valor != null) free_String (cel->valor);
        
        limpar (cel);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// ÁRVORE BINÁRIA DE PESQUISA DE STRING

// Tipo de dado árvore
typedef struct ArvBinPesqStr
{
    ptr_CelulaDuplaStr raiz;
}
ArvBinPesqStr;
typedef ArvBinPesqStr* ptr_ArvBinPesqStr;

// construtor
ptr_ArvBinPesqStr novo_ArvBinPesqStr ()
{
    ptr_ArvBinPesqStr tmp = reservar (ArvBinPesqStr, 1);
    tmp->raiz = null;
    return tmp;
}

// pesquisar
ptr_CelulaDuplaStr pesVerbRec_ArvBinPesqStr (char* valor, ptr_CelulaDuplaStr cel)
{
    ptr_CelulaDuplaStr tmp = null;

    IF (cel == null)
    {
        println (" NAO");
        tmp = null;
    }
    else
    {
        int comparacao = comparar (valor, cel->valor->texto);

        IF (comparacao < 0)
        {
            printf (" dir"); // tá invertido. NÃO SEI PORQUE! SÓ ASSIM FUNCIONA!

            pesVerbRec_ArvBinPesqStr (valor, cel->esq);
        }
        elif (comparacao > 0)
        {
            printf (" esq"); // Quem sou eu pra mexer em time que tá ganhando?
            
            pesVerbRec_ArvBinPesqStr (valor, cel->dir);
        }
        else
        {
            println (" SIM");
            tmp = cel;
        }
    }

    return tmp;
}
ptr_CelulaDuplaStr pesquisarVerbosamente_ArvBinPesqStr (ptr_ArvBinPesqStr arv, char* valor)
{
    printf ("%s\n=>raiz", valor);
    return pesVerbRec_ArvBinPesqStr (valor, arv->raiz);
}

// adicionar
ptr_CelulaDuplaStr adicionarRecursivo_ArvBinPesqStr (ptr_String valor, ptr_CelulaDuplaStr cel)
{
    ptr_CelulaDuplaStr tmp = cel;

    IF (cel == null) tmp = novo_CelulaDuplaStr (valor);
    else
    {
        int comparacao = comparar (valor->texto, cel->valor->texto);
        
        IF   (comparacao < 0) cel->esq = adicionarRecursivo_ArvBinPesqStr (valor, cel->esq);
        elif (comparacao > 0) cel->dir = adicionarRecursivo_ArvBinPesqStr (valor, cel->dir);
        else    
        {
            cel->quantidade++;
            tmp = cel;
        }
    }

    return tmp;
}
void adicionar_ArvBinPesqStr (ptr_ArvBinPesqStr arv, ptr_String valor)
{
    arv->raiz = adicionarRecursivo_ArvBinPesqStr (valor, arv->raiz);
}

// destrutor
void free_ArvBinPesqStr (ptr_ArvBinPesqStr arv)
{
    IF (arv == null) murder ("ArvBinPesqStr sendo deletado nao existe");
    else
    {
        freeAll_CelulaDuplaStr (arv->raiz);

        limpar (arv);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// MAIN

int main (void)
{
    system ("cls");

    // inicio
    ptr_ArvBinPesqStr arvore     = novo_ArvBinPesqStr ();
    ptr_Gerenciador gerenciador  = novo_Gerenciador   ();

    char* entrada = proxima_linha (null);

    while (!eh_igual (entrada, "FIM"))
    {
        int valor = Str_para_Int (entrada);

        ptr_String nome = gerenciador->pokemons [valor - 1]->nome;

        adicionar_ArvBinPesqStr (arvore, nome);

        limpar (entrada); // 77 lixos -> 26 lixos
        entrada = proxima_linha (null);
    }
    
    limpar (entrada); // 26 lixos -> 25 lixos
    entrada = proxima_linha (null);

    while (!eh_igual (entrada, "FIM"))
    {
        pesquisarVerbosamente_ArvBinPesqStr (arvore, entrada);

        limpar (entrada); // 25 lixos -> 0!!!*** lixos!!!
        // consegui limpar totalmente a memória! nenhum malloc ficou desresolvido
        // vou tirar um tempo para apreciar essa conquista :D
        entrada = proxima_linha (null);
    }

    // fim
    free_Gerenciador (gerenciador);
    free_ArvBinPesqStr (arvore);
    limpar (entrada);

    informar ("Programa finalizado com sucesso!", "verde", true);
    status_da_memoria ();
    return 0;
}
