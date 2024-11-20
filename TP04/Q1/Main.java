/**
 * @date: 11/2024
 * @author: Thiago Pereira de Oliveira
 * @details: Meu código fonte dos TPs para Java, onde guardo a base para as futuras atividades
 * do TP 4.
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////
// BIBLIOTECAS

import java.io.PrintWriter;    // escrever em um arquivo
import java.util.Scanner;     // não sei criar scanners do zero
import java.io.File;         // nem fazer arquivos do zero ainda

/////////////////////////////////////////////////////////////////////////////////////////////////////
// CORE

// classe de armazenamento / funções interessantes de se ter como um todo. Um QOL no geral.
class Core
{
    public static boolean verde = false;
    public static int comparacoes = 0;

    // função de finalização
    public static void finalizar (long inicio) throws Exception
    {
        long fim = System.nanoTime ();
        // tempo de execução em nanosegundos
        long tempo_de_execucao = fim - inicio;

        // espero não ser essencial escrever o resto, porque não tô a fim
        File arquivo = new File ("Matrícula.txt"); 
        PrintWriter escritor = new PrintWriter (arquivo);
        escritor.print("Matricula: 835251 \t Tempo de execução (em ms): " + tempo_de_execucao + "\tComparações: " + comparacoes);
        escritor.close ();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// LISTA DE STRING ESTÁTICA

// definindo a lista de String estática
class Lista_SE
{
    // VARS
    private String [] lista;
    private int tamanho = 0;
    private int x = 0;

    // adicionar
    public void adicionar (String valor) throws Exception
    {
        if (valor == null) throw new Exception ("Valor inexistente em adicionar na LDSE!");
            else if (x >= tamanho) throw new Exception ("LDSE muito pequena!");
                else lista [x++] = valor;
    }

    // imprimir
    public void imprimir ()
    {
        for (int x = 0; x < this.x; x++)
            System.out.println ("[" + x + "] (tam" + lista [x].length () + ") " + lista [x]);
    }

    // construtor
    public Lista_SE (int tamanho)
    {
        lista = new String [tamanho];
        this.tamanho = tamanho;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// DATA

// tipo de dado Data
class Data
{
    // VARS
    private int dia = 0;
    private int mes = 0;
    private int ano = 0;

    // converte Data para String
    public String para_String ()
    {
        return ((dia > 9)?"":"0") + dia + "/" + ((mes > 9)?"":"0") + mes + "/" + ano;
    }

    // construtor
    public Data (String texto)
    {
        String [] cut = texto.split ("/");

        dia = Integer.parseInt (cut [0]);
        mes = Integer.parseInt (cut [1]);
        ano = Integer.parseInt (cut [2]);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// POKEMON

// classe pokemon
class Pokemon
{
    // VARS
    private int Id = 0;
    private int geracao = 0;
    private String nome = "";
    private String descricao = "";
    private Lista_SE tipos = new Lista_SE (2);
    private Lista_SE habilidades = new Lista_SE (1);
    private double peso = 0.0;
    private double tamanho = 0.0;
    private int razao_de_captura = 0;
    private boolean eh_lendario = false;
    private Data Data_de_captura = new Data ("0/0/0");

    // GETS
    public int getId () {return Id;}
    public int getGeracao () {return  geracao;}
    public String getNome () {return nome;}
    public String getDescricao () {return descricao;}
    public Lista_SE getTipos () {return tipos;}
    public Lista_SE getHabilidades () {return habilidades;}
    public double getPeso () {return peso;}
    public double getTamanho () {return tamanho;}
    public int getRazao_de_captura () {return razao_de_captura;}
    public boolean getEh_lendario () {return eh_lendario;}
    public Data getData_de_captura () {return Data_de_captura;}

    // Ler uma string para construir o Pokemon
    public void ler (String entrada) throws Exception
    {
        //int quantas_partes = 0;
        String [] corte = entrada.split ("\"");

        // --- parte antes de habilidades (corte [0])
        int quantos_corte_0 = 0;

        String [] corte_0 = corte [0].replaceAll ("^,+|,+$", "").split (",");
        quantos_corte_0 = corte_0.length;

        // Id
        this.Id = Integer.parseInt (corte_0 [0]);

        // Geração
        this.geracao = Integer.parseInt (corte_0 [1]);

        // Nome
        this.nome = corte_0 [2];

        // Descrição
        this.descricao = corte_0 [3];

        // Tipos
        this.tipos.adicionar (corte_0 [4]);
        if (quantos_corte_0 == 6)
        this.tipos.adicionar (corte_0 [5]);

        // --- habilidades (corte [1])
        int quantos_corte_1 = 0;

        String [] corte_1 = corte [1].replaceAll("[\\['\\]']", "").split (", ");
        quantos_corte_1 = corte_1.length;

        this.habilidades = new Lista_SE (quantos_corte_1);

        for (int x = 0; x < quantos_corte_1; x++)
            this.habilidades.adicionar (corte_1 [x]);

        // --- outros (corte [2])
        //int quantos_corte_2 = 0;
        corte [2] = corte [2].substring (1);

        String [] corte_2 = corte [2].split (",");

        // Peso
        if (corte_2 [0].length () != 0) this.peso = Double.parseDouble (corte_2 [0]);

        // Tamanho
        if (corte_2 [1].length () != 0) this.tamanho = Double.parseDouble (corte_2 [1]);

        // Razão
        this.razao_de_captura = Integer.parseInt (corte_2 [2]);

        // É lendário
        this.eh_lendario = (corte_2 [3].equals ("1"))?true:false;

        // Data
        this.Data_de_captura = new Data (corte_2 [4]);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// GERENCIADOR

// classe que gerencia pokemons.
class Gerenciador
{
    // VARS
    private int quantos = 801;
    private Pokemon pokemons [] = new Pokemon [quantos];

    // GETS
    public Pokemon getPokemon (int Id) {return pokemons [Id - 1];}

    // todos os nomes
    public void imprimir_nomes ()
    {
        int quantos = this.quantos;

        for (int x = 0; x < quantos; x++)
            System.out.println (pokemons [x].getNome ());
    }

    // todos os tipos
    public void imprimir_tipos ()
    {
        int quantos = this.quantos;

        for (int x = 0; x < quantos; x++)
        {
            System.out.println ("\nID " + (x+1));
            pokemons [x].getTipos ().imprimir ();
        }
    }

    // todas habilidades
    public void imprimir_habilidades ()
    {
        int quantos = this.quantos;

        for (int x = 0; x < quantos; x++)
        {
            System.out.println ("\nID " + (x+1));
            pokemons [x].getHabilidades ().imprimir ();
        }
    }

    // todos tamanhos
    public void imprimir_tamanhos ()
    {
        int quantos = this.quantos;

        for (int x = 0; x < quantos; x++)
        {
            System.out.println ("\nID " + (x+1));
            System.out.println (this.pokemons [x].getTamanho ());
        }
    }

    // todas datas
    public void imprimir_datas ()
    {
        int quantos = this.quantos;

        for (int x = 0; x < quantos; x++)
        {
            System.out.println ("\nID " + (x+1));
            System.out.println (this.pokemons [x].getData_de_captura ().para_String ());
        }
    }

    // construtor
    public Gerenciador () throws Exception
    {
        File arquivo = new File ("../pokemon.csv");

        if (!arquivo.exists ())
        {
            arquivo = new File ("/tmp/pokemon.csv");

            if (!arquivo.exists ()) 
            throw new Exception ("Arquivo .CSV não encontrado!");

            Core.verde = true;
        }

        Scanner scanner = new Scanner (arquivo);
        scanner.nextLine (); // remover cabeçalho

        for (int x = 0; x < quantos; x++)
        {
            pokemons [x] = new Pokemon ();
            pokemons [x].ler (scanner.nextLine ());
        }

        scanner.close ();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// CÉLULA DUPLA STRING

// Tipo de dado da célula duplamente encadeada. Tanto para listas quanto para árvores
class CelulaDuplaStr
{
    // VARS
    public CelulaDuplaStr esq = null;
    public CelulaDuplaStr dir = null;
    public String valor = ""; 

    public int quantidade = 1; // valores extra de utilidade

    // construtor
    public CelulaDuplaStr (String valor)
    {
        this.valor = valor;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// ÁRVORE BINÁRIA DE PESQUISA

// Tipo de dado Árvore Binária de pesquisa com String
class ArvoreBinariaDePesquisaStr
{
    // VARS
    private CelulaDuplaStr raiz = null;

    // adicionar
    public void adicionar (String valor)
    {
        raiz = adicionar (valor, raiz);
    }    
    private CelulaDuplaStr adicionar (String valor, CelulaDuplaStr celula)
    {
        CelulaDuplaStr tmp = celula;
        Core.comparacoes++;

        if (celula == null) tmp = new CelulaDuplaStr (valor);
        else
        {
            int comparacao = valor.compareTo (celula.valor);

            if      (comparacao < 0) celula.esq = adicionar (valor, celula.esq);
            else if (comparacao > 0) celula.dir = adicionar (valor, celula.dir);
            else    
            {
                celula.quantidade++;
                tmp = celula;
            }
        }

        return tmp;
    }

    // pesquisar
    public CelulaDuplaStr pesquisar_verbosamente (String valor)
    {
        System.out.print (valor + "\n=>raiz");
        return pesquisar_verbosamente (valor, raiz);
    }
    private CelulaDuplaStr pesquisar_verbosamente (String valor, CelulaDuplaStr celula)
    {
        CelulaDuplaStr tmp = null;
        Core.comparacoes++;

        if (celula == null)
        {
            System.out.println (" NAO");
            tmp = null;
        }
        else
        {
            int comparacao = valor.compareTo (celula.valor);
            
            if (comparacao < 0)
            {
                System.out.print (" esq");
                pesquisar_verbosamente (valor, celula.esq);
            } 
            else if (comparacao > 0)
            {
                System.out.print (" dir");
                pesquisar_verbosamente (valor, celula.dir);
            }
            else    
            {
                System.out.println (" SIM");
                tmp = celula;
            } 
        }

        return tmp;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// MAIN

public class Main
{
    public static void main (String args []) throws Exception
    {
        long inicio = System.nanoTime ();

        ArvoreBinariaDePesquisaStr arvore = new ArvoreBinariaDePesquisaStr ();
        Gerenciador pokemons = new Gerenciador ();
        Scanner scanner = new Scanner (System.in);

        String entrada = scanner.nextLine ();
        while (!entrada.equals ("FIM"))
        {
            Core.comparacoes++;
            int valor = Integer.parseInt (entrada);

            String nome = pokemons.getPokemon (valor).getNome ();

            arvore.adicionar (nome);

            entrada = scanner.nextLine ();
        }

        entrada = scanner.nextLine ();
        while (!entrada.equals ("FIM"))
        {
            Core.comparacoes++;
            arvore.pesquisar_verbosamente (entrada);

            entrada = scanner.nextLine ();
        }

        Core.finalizar (inicio);
        scanner.close ();
    }
}