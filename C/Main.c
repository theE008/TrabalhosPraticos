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

/////////////////////////////////////////////////////////////////////////////////////////////////////
// QOL

// malloc mais simples/seguro
#define reservar(tipo,quantos) (tipo*) reservar_espaco_funcao (quantos*sizeof (tipo)); 

// cria uma linha fácil de ver e remover que printa o número da linha onde está
#define DEBUGLINE_DEBUGLINE_DEBUGLINE_DEBUGLINE_DEBUGLINE \
if (!verde) printf ("\n\tDebug reached line %d\n", __LINE__)

// for simplificado
#define loop(quantas_vezes,var) for(int var = 0; var < quantas_vezes; var++)

// else if
#define elif else if

// usando o null do java
#define null NULL

// println
#define println(...) printf (__VA_ARGS__); printf ("\n");

/////////////////////////////////////////////////////////////////////////////////////////////////////
// BOOLEAN & NÚMEROS NATURAIS

typedef unsigned int nat; // numeros naturais

typedef enum { false = 0, true = 1 } boolean;

/////////////////////////////////////////////////////////////////////////////////////////////////////
// CORE

boolean eh_igual (char* t1, char* t2);
boolean verde = false;

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

    if   (eh_igual (text, "negrito"     )) texto =  1;
    elif (eh_igual (text, "sublinhado"  )) texto =  4;
    elif (eh_igual (text, "preto"       )) texto = 30;
    elif (eh_igual (text, "vermelho"    )) texto = 31;
    elif (eh_igual (text, "verde"       )) texto = 32;
    elif (eh_igual (text, "amarelo"     )) texto = 33;
    elif (eh_igual (text, "azul"        )) texto = 34;
    elif (eh_igual (text, "magenta"     )) texto = 35;
    elif (eh_igual (text, "ciano"       )) texto = 36;
    elif (eh_igual (text, "branco"      )) texto = 37;

    if   (eh_igual (background, "preto"         )) fundo = 40;
    elif (eh_igual (background, "vermelho"      )) fundo = 41;
    elif (eh_igual (background, "verde"         )) fundo = 42;
    elif (eh_igual (background, "amarelo"       )) fundo = 43;
    elif (eh_igual (background, "azul"          )) fundo = 44;
    elif (eh_igual (background, "magenta"       )) fundo = 45;
    elif (eh_igual (background, "ciano"         )) fundo = 46;
    elif (eh_igual (background, "branco"        )) fundo = 47;

    printf ("\033[%d;%dm",texto, fundo);
}

// mensagem colorida
void mensagem_colorida (char* mensagem, char* cor, boolean importante)
{
    colorir (cor, "preto");
    if (importante) important (mensagem);
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
    if (!verde) mensagem_colorida (entrada, cor, importante);
}

// malloc mais seguro
void* reservar_espaco_funcao (size_t Size)
{
    void* try = malloc (Size);

    if (try != null)
    return try;
    else
    {
        murder ("Erro ao criar espaco");
    }
}

// calloc
char* reservar_string (size_t quantos)
{
    if (quantos <= 0) murder ("Alocando memoria nula");
    char* tmp = (char*) reservar_espaco_funcao (quantos);

    loop (quantos, x) tmp [x] = '*';

    return tmp;
}

// nextLine
char* proxima_linha (FILE* arquivo)
{
    char *saida = reservar (char, 500);
    if (fscanf (arquivo, "%[^\n]\n", saida) != 1) murder ("Arquivo lido alem da conta");

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
    if (entrada == null) murder ("Impossivel pegar tamanho de string inexistente");
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

    if (tam1 != tamanho (t2)) resposta = false;
    else
    {
        for (int x = 0; x < tam1 && resposta; x++)
            if (t1 [x] != t2 [x]) resposta = false;
    }

    return resposta;
}

// Strcpy. Retorna o tamanho da string (em caracteres) final.
int copiar_texto (char* t1, char* t2)
{
    int x = 0;

    if (tamanho (t1) >= tamanho (t2))
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
    if (texto == null) murder ("Texto inexistente em contar um caractere");
    else
    {
        int tam = tamanho (texto);
        int resposta = 0;

        loop (tam, x) if (texto [x] == carac) resposta++;

        return resposta;
    }
}

// Split para C
char** separar (char* texto, char carac, int *saida_de_quantos)
{
    if (texto == null) murder ("Texto inexistente em separar");
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
            if (texto [x] == carac)
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

        if (saida_de_quantos != null) *saida_de_quantos = quantos; 
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
    if ('0' <= carac && carac <= '9')
    {
        return carac - '0';
    }
    else
        murder ("Caractere nao numerico nao pode virar numero");
}

// parseInt
int Str_para_Int (char* str)
{
    if (str == null) murder ("Texto inexistente em Str_para_Int");
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
    if (val > 9) murder ("Valor muito grande");
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
    if (str == null) murder ("Texto inexistente em Str_para_Dbl");
    else
    {
        char** partes = separar (str, '.', null);
        double resposta = 0;

        // casas depois da virgula;
        int casas = tamanho (partes [1]);

        resposta  = Str_para_Int (partes [0]);
        double p2 = Str_para_Int (partes [1]);

        resposta += p2 / (double) potencia (10, casas);

        return resposta;
    }
}

// verifica se a string tem um caractere em especifico
boolean contem_caractere (char* entrada, char carac)
{
    if (entrada == null) murder ("Entrada invalida em contem caractere");
    else
    {
        int tam = tamanho (entrada);
        boolean resposta = false;

        for (int x = 0; x < tam && !resposta; x++) 
            if (entrada [x] == carac)
                resposta = true;
        
        return resposta;
    }
}

// remove espaços do inicio e do final se existirem
char* trim (char* entrada)
{
    if (entrada == null) murder ("Trim com entrada invalida");
    else
    {
        int tam = tamanho (entrada);
        char* saida = reservar_string (tam + 1);
        int y = 0;

        loop ((tam - 1), x)
        {
            if (x == 0)
            {
                if (entrada [0] != ' ')
                saida [y++] = entrada [x];
            }
            else
            saida [y++] = entrada [x];
        }

        if (entrada [tam - 1] == ' ')
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
    if (texto == null || remocoes == null) murder ("Entradas invalidas em remover caracteres");
    else
    {
        int tam = tamanho (texto);
        char* resposta = reservar_string (tam);
        int index = 0;

        loop (tam, x)
        {
            if (!contem_caractere (remocoes, texto [x]))
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
    if (t1 == null || t2 == null) murder ("Texto inexistente em concatenar");
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

// recebe um numero e o transforma em string
char* Int_para_Str (int val)
{
    char* resposta;

    if (val != 0)  
        resposta = concatenar (Int_para_Str (val/10), char_para_Str (Int_para_char (val % 10)));
    else resposta = "";

    return resposta;
}

// insere caracteres no inicio se o tamanho nao for o correto
char* garantir_tamanho (char* entrada, int tam, char carac)
{
    if (entrada == null) murder ("Entrada indefinida em garantir tamanho");
    else
    {
        int tama = tamanho (entrada);
        char* resposta;

        if (tam > tama)
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
typedef String* ref_String;
void free_String (ref_String str); 

// construtor
ref_String novo_String (char* entrada)
{
    ref_String tmp = reservar (String, 1);

    if (entrada == null)
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
void alterar_String (String **str, char* texto)
{
    if (str == null || texto == null)
        murder ("Valor inexistente em alterar String");
    {
        free_String (*str);
        *str = reservar (String, 1);
        *str = novo_String (texto);
    }
}

// destrutor
void free_String (ref_String str)
{
    if (str != null)
    {
        free (str->texto);

        free (str);
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
typedef Lista_de_String_Estatica* ref_Lista_de_String_Estatica;

// construtor
ref_Lista_de_String_Estatica novo_LdSe (int tamanho)
{
    ref_Lista_de_String_Estatica tmp = reservar (Lista_de_String_Estatica, 1);

    tmp->tamanho = tamanho;
    tmp->x = 0;

    tmp->lista = reservar (ref_String, tamanho);

    loop (tamanho, x)
    {
        tmp->lista [x] = novo_String (null);
    }

    return tmp;
}

// adicionar
void adicionar_na_LdSe (ref_Lista_de_String_Estatica lista, ref_String valor)
{
    if (lista == null || valor == null) murder ("Valor inexistente em adicionar na LDSE");
        elif (lista->x >= lista->tamanho) murder ("LdSe muito pequena");
            else lista->lista [lista->x++] = valor;
}

// imprime todos os elementos
void imprimir_LdSe (ref_Lista_de_String_Estatica lista)
{
    if (lista == null) murder ("Lista inexistente em impressao");

    loop (lista->x, x)
    {
        println ("[%d] (tam %d) %s", x, lista->lista [x]->tamanho, lista->lista [x]->texto);
    }

    println (null);
}

// destrutor
void free_LdSe (ref_Lista_de_String_Estatica lista)
{
    if (lista != null)
    {
        loop (lista->tamanho, x)
        {
            free_String (lista->lista [x]);
        }
        
        free (lista);
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
typedef Data* ref_Data;

// construtor
ref_Data novo_Data (char* texto)
{
    ref_Data tmp = reservar (Data, 1);
    tmp->dia = 0;
    tmp->mes = 0;
    tmp->ano = 0;

    if (texto != null)
    {
        char** cut = separar (texto, '/', null);

        tmp->dia = Str_para_Int (cut [0]);
        tmp->mes = Str_para_Int (cut [1]);
        tmp->ano = Str_para_Int (cut [2]);
    }

    return tmp;
}

char* Data_para_Str (ref_Data data)
{
    return concatenar( concatenar( concatenar (concatenar (garantir_tamanho (Int_para_Str (data->dia), 2, '0'), "/"), 
    garantir_tamanho (Int_para_Str (data->mes), 2, '0')), "/"), garantir_tamanho (Int_para_Str (data->ano), 4, '0'));
}

// destrutor
void free_Data (ref_Data data)
{
    if (data != null)
    {
        free (data);
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
    ref_String nome;
    ref_String descricao;
    ref_Lista_de_String_Estatica tipos;
    ref_Lista_de_String_Estatica habilidades;
    double peso;
    double tamanho;
    int razao_de_captura;
    boolean eh_lendario;
    ref_Data Data_de_captura;
}
Pokemon;
typedef Pokemon* ref_Pokemon;

// construtor
ref_Pokemon novo_Pokemon ()
{
    ref_Pokemon tmp = reservar (Pokemon, 1);

    tmp->Id = 0;
    tmp->geracao = 0;
    tmp->nome = novo_String (null);
    tmp->descricao = novo_String (null);
    tmp->tipos = novo_LdSe (2);
    tmp->habilidades = novo_LdSe (1);
    tmp->peso = 0;
    tmp->tamanho = 0;
    tmp->razao_de_captura = 0;
    tmp->eh_lendario = false;
    tmp->Data_de_captura = novo_Data (null);

    return tmp;
}

// ler
void ler_Pokemon (ref_Pokemon poke, char* texto)
{
    int quantas_partes = 0;
    char ** corte = separar (texto, '"', &quantas_partes);

    // --- parte antes de habilidades (corte [0])
    int quantos_corte_0 = 0;

    int tam = tamanho (corte [0]);
    corte [0] [tam - 1] = '\0';
    if (corte [0] [tam - 2] == ',')
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
    if (quantos_corte_0 == 6) 
    adicionar_na_LdSe (poke->tipos, novo_String (corte_0 [5]));

    // --- habilidades (corte [1])
    int quantos_corte_1 = 0;

    char ** corte_1 = separar (remover_caracteres (corte [1], "[]'"), ',', &quantos_corte_1);

    free_LdSe (poke->habilidades);
    poke->habilidades = novo_LdSe (quantos_corte_1);

    loop (quantos_corte_1, x)
    adicionar_na_LdSe (poke->habilidades, novo_String (trim (corte_1 [x])));

    // --- outros (corte [2])
    int quantos_corte_2 = 0;
    corte [2] [0] = ' ';

    char ** corte_2 = separar (trim (corte [2]), ',', &quantos_corte_2);

    // Peso
    if (tamanho (corte_2 [0])) poke->peso = Str_para_Dbl (corte_2 [0]);

    // Tamanho
    if (tamanho (corte_2 [1])) poke->tamanho = Str_para_Dbl (corte_2 [1]);

    // Razão
    poke->razao_de_captura = Str_para_Int (corte_2 [2]);

    // É lendário
    poke->eh_lendario = Str_para_Int (corte_2 [3]);

    // Data
    free_Data (poke->Data_de_captura);
    poke->Data_de_captura = novo_Data (corte_2 [4]);
}

// destrutor
void free_Pokemon (ref_Pokemon poke)
{
    if (poke != null)
    {
        free_String (poke->descricao);
        free_LdSe   (poke->tipos);
        free_String (poke->nome);
        
        free (poke);
    }
    else
        murder ("Pokemon sendo deletado nao existe");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/// GERENCIADOR

// tipo de dado Gerenciador
typedef struct Gerenciador
{
    int quantos_pokemons;
    Pokemon **pokemons;
}
Gerenciador;
typedef Gerenciador* ref_Gerenciador;

// construtor 
ref_Gerenciador novo_Gerenciador ()
{
    ref_Gerenciador tmp = reservar (Gerenciador, 1);
    int quantos_pokemons = 801;

    FILE* arquivo = fopen ("../pokemon.csv", "rt");

    if (arquivo == null)
    {
        arquivo = fopen ("/tmp/pokemon.csv", "rt");

        if (arquivo == null) murder ("Arquivo CSV inexistente.");

        verde = true;
    }

    tmp->pokemons = reservar (ref_Pokemon, quantos_pokemons);
    tmp->quantos_pokemons = quantos_pokemons;

    proxima_linha (arquivo);

    loop (quantos_pokemons, x)
    {
        tmp->pokemons [x] = novo_Pokemon ();
        
        ler_Pokemon (tmp->pokemons [x], proxima_linha (arquivo));
    }

    fclose (arquivo);
    return tmp;
}

// todos os nomes
void imprimir_nomes_Gerenciador (ref_Gerenciador gere)
{
    int quantos = gere->quantos_pokemons;

    loop (quantos, x)
    {
        printf ("%s\n", gere->pokemons [x]->nome->texto);
    }
}

// todos os tipos
void imprimir_tipos_Gerenciador (ref_Gerenciador gere)
{
    int quantos = gere->quantos_pokemons;

    loop (quantos, x)
    {
        println ("ID %d", x + 1);
        imprimir_LdSe (gere->pokemons [x]->tipos);
    }
}

// todas as habilidades
void imprimir_habilidades_Gerenciador (ref_Gerenciador gere)
{
    int quantos = gere->quantos_pokemons;

    loop (quantos, x)
    {
        println ("ID %d", x + 1);
        imprimir_LdSe (gere->pokemons [x]->habilidades);
    }
}

// todos tamanhos
void imprimir_tamanhos_Gerenciador (ref_Gerenciador gere)
{
    int quantos = gere->quantos_pokemons;

    loop (quantos, x)
    {
        println ("ID %d", x + 1);
        println ("%lf", gere->pokemons [x]->tamanho);
    }
}

// todas datas
void imprimir_datas_Gerenciador (ref_Gerenciador gere)
{
    int quantos = gere->quantos_pokemons;

    loop (quantos, x)
    {
        println ("ID %d", x + 1);
        println ("%s", Data_para_Str (gere->pokemons [x]->Data_de_captura));
    }
}

// destrutor
void free_Gerenciador (ref_Gerenciador gere)
{
    if (gere != null)
    {
        loop (gere->quantos_pokemons, x)
            free_Pokemon (gere->pokemons [x]);

        free (gere);
    }
    else
        murder ("Gerenciador sendo deletado nao existe");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// MAIN

int main (void)
{
    ref_Gerenciador gerenciador = novo_Gerenciador ();
    imprimir_datas_Gerenciador (gerenciador);

    // fim
    free_Gerenciador (gerenciador);
    informar ("Programa finalizado com sucesso", "verde", true);
    return 0;
}
