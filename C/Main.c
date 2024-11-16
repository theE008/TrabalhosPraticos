#include <stdlib.h>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////
// LASS

// Definição de classe em C (Lass)
#define Class(name) typedef struct name name; struct name
#define METHODS_OF_CLASS void (*clear) (void);};
#define CONSTRUTOR_OF(val, ...) val* novo_##val (__VA_ARGS__){ val* tmp = (val*) malloc (sizeof (val)); tmp->clear = val##_clear;
#define END_OF_CONSTRUTOR this = tmp; return tmp; if(0)
#define set_public(val) tmp->val = val;
#define DESTRUTOR_OF(val) void val##_clear ()
#define atual(val) this = &val; val

// QOL
#define reservar(val,vlr) (val*) reservar_espaco_funcao (vlr*sizeof (val)); 
#define loop(val,var) for(int var = 0; var < val; var++)
#define null NULL
#define elif else if
void* this;

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

// calloc
char* reservar_string (int quantos)
{
    char* tmp = (char*) reservar_espaco_funcao (quantos);

    loop (quantos, x) tmp [x] = '*';

    return tmp;
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

// Concatenar
char* conc (char* t1, char* t2)
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

/////////////////////////////////////////////////////////////////////////////////////////////////////
// STRING

// Tipo String
Class (String)
{
    char *valor;
    int tamanho;

    METHODS_OF_CLASS;

    DESTRUTOR_OF (String)
    {
        printf ("%s\n", ((String*)this)->valor);

        free (((String*)this)->valor);
    }

    CONSTRUTOR_OF (String, char* texto)
    {
        int tam = tamanho (texto);

        if (tmp == null) murder ("Falha de alocacao em nova_String.");

        tmp->valor = reservar_string (tam + 1);
        if (tmp->valor == null) murder ("Falha de alocacao 2 em nova_String.");

        tmp->tamanho = copiar_texto (tmp->valor, texto);

        END_OF_CONSTRUTOR;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// POKEMON

Class (Pokemon)
{
    String          *description;
    int             generation;
    String          *name;
    int             Id;

    void (*ler) (String entrada);

    METHODS_OF_CLASS;

    // destrutor
    DESTRUTOR_OF (Pokemon)
    {
        Pokemon *P = ((Pokemon*) this);

        this = P->description; P->description->clear ();
        this = P->name; P->name->clear ();

        this = P;

        free (P);
    }

    void ler (String entrada)
    {
        printf ("%d\n",entrada.tamanho);
    }

    // construtor
    CONSTRUTOR_OF (Pokemon)
    {
        tmp->description = novo_String ("ama");
        tmp->name = novo_String ("ama");

        set_public (ler);

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

    METHODS_OF_CLASS;

    // destrutor
    DESTRUTOR_OF (Gerenciador)
    {
        fclose (((Gerenciador*) this) -> arquivo);

        int quantos = ((Gerenciador*) this)->quantos;

        loop (quantos, x) 
        {
            Pokemon *tmp = &((Gerenciador*) this)->pokemons [x];

            Gerenciador *G = (Gerenciador*) this;
            this = tmp;

            tmp->clear ();

            this = G;
        }

        free (((Gerenciador*) this)->pokemons);
    }

    // Construtor do tipo Gerenciador
    CONSTRUTOR_OF (Gerenciador)
    {
        int quantos = 801;

        tmp->quantos = quantos;

        tmp->pokemons = reservar (Pokemon, 801);
        loop (quantos, x) tmp->pokemons [x] = *novo_Pokemon ();

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

        char entrada [500] = "";
        int cont = 0;

        while (fscanf (tmp->arquivo, "%[^\n]\n", entrada) == 1) 
        {
            String *tim = novo_String (entrada);

            this = &tmp->pokemons [cont];

            ((Pokemon*) this)->ler (*tim);
        }

        END_OF_CONSTRUTOR;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// MAIN

void main (void)
{
    Gerenciador *pokemons = novo_Gerenciador ();

    pokemons->clear ();
}