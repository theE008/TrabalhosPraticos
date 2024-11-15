#include <stdlib.h>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////
// LASS

// Definição de classe em C (Lass)
#define Class(name) typedef struct name name; struct name
#define METHODS_OF_CLASS };
#define CONSTRUTOR_OF(val, ...) val* novo_##val (__VA_ARGS__){ val* tmp = (val*) malloc (sizeof (val));
#define END_OF_CONSTRUTOR this = tmp; return tmp; if(0)
#define set_public(val) tmp->val = val;

// QOL
#define reservar(val,vlr) (val*) reservar_espaco_funcao (vlr*sizeof (val)); 
#define loop(val,var) for(int var = 0; var < val; var++)
#define null NULL
#define elif else if
void* this;

/////////////////////////////////////////////////////////////////////////////////////////////////////
// CLASS SKELETON

// Classe esqueleto para cópia e referência
Class (ESQUELETO)
{
    // variaveis

    // metodos publicos

    METHODS_OF_CLASS;
    // metodos

    // construtor final
    CONSTRUTOR_OF (ESQUELETO)
    {
        // definição

        // setting de métodos públicos

        END_OF_CONSTRUTOR;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// BOOLEAN

typedef short int boolean;
const boolean true    = 1;
const boolean false   = 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////
// CORE

boolean eh_igual (char* t1, char* t2);

// Texto levemente destacado.
void important (char* entrada)
{
    printf ("\n\n\t%s\n\n", entrada);
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

// Mensagem de erro
void murder (char* entrada)
{
    colorir ("vermelho", "preto");
    important (entrada); 
    colorir ("branco", "preto");

    exit (-1);
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

/////////////////////////////////////////////////////////////////////////////////////////////////////
// TEXTOS

// Retorna a quantia de caracteres presente em uma string.
int tamanho (char* entrada)
{
    int resposta = 0;

    while (entrada [resposta] != '\0') resposta++;

    return resposta;
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

// Strcpy. Retorna o tamanho da string final.
int copiar_texto (char* t1, char* t2)
{
    int x = 0;

    if (tamanho (t1) >= tamanho (t2))
    {
        char c = 0;

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

/////////////////////////////////////////////////////////////////////////////////////////////////////
// STRING

// Tipo String
typedef struct String
{
    char *valor;
    int tamanho;
} 
String;

// Construtor do tipo String
String* nova_String (char* texto)
{
    String *tmp = reservar (String, 1);
    int tam = tamanho (texto);

    if (tmp == null) murder ("Falha de alocacao em nova_String.");

    tmp->valor = reservar (char, (tam + 1));
    if (tmp->valor == null) murder ("Falha de alocacao 2 em nova_String.");

    tmp->tamanho = copiar_texto (tmp->valor, texto);

    return tmp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// POKEMON

Class (Pokemon)
{
    METHODS_OF_CLASS;

    CONSTRUTOR_OF (Pokemon)
    {

        END_OF_CONSTRUTOR;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// GERENCIADOR

// Tipo Gerenciador
Class (Gerenciador)
{
    Pokemon* pokemons;
    boolean     verde;
    FILE*     arquivo;
    int       quantos;
    String*  entradas;

    void (*imprimir_Arquivo) (void);

    METHODS_OF_CLASS;

    // print de debug
    void imprimir_Arquivo ()
    {
        char entrada [500] = "";

        while (fscanf (((Gerenciador*) this)->arquivo, "%[^\n]\n", entrada) == 1) printf ("%s!!!%d\n", entrada, tamanho (entrada));
    }

    // Construtor do tipo Gerenciador
    CONSTRUTOR_OF (Gerenciador)
    {
        int quantos = 801;

        tmp->quantos = quantos;

        tmp->pokemons = reservar (Pokemon, quantos);

        tmp->entradas = reservar (String, 801); //

        tmp->arquivo = fopen ("../pokemon.csv", "rt");
        tmp->verde = false;

        if (tmp->arquivo == null)
        {
            tmp->arquivo = fopen ("/tmp/pokemon.csv", "rt");
            tmp->verde = true;

            if (tmp->arquivo == null)
            {
                murder ("O arquivo pokemon.csv nao existe ou estah inacessivel!");
            }
        }

        set_public (imprimir_Arquivo);

        END_OF_CONSTRUTOR;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// MAIN

void main (void)
{
    Gerenciador *pokemons = novo_Gerenciador ();

    pokemons->imprimir_Arquivo ();

    reservar (Gerenciador, 999999999);
}