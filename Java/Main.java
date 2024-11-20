/**
 * @date: 11/2024
 * @author: Thiago Pereira de Oliveira
 * @details: Meu código fonte dos TPs para Java, onde guardo a base para as futuras atividades
 * do TP 4.
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////
// BIBLIOTECAS

import java.io.File; // não sei fazer arquivos do zero ainda
import java.util.Scanner;     // nem criar scanners do zero

/////////////////////////////////////////////////////////////////////////////////////////////////////
// CORE

// classe de armazenamento / funções interessantes de se ter como um todo. Um QOL no geral.
class Core
{
    public static boolean verde = false;
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
    //data

    // GETS
    public int getId () {return Id;}
    public int getGeracao () {return  geracao;}
    public String getNome () {return nome;}
    public String getDescricao () {return descricao;}
    public Lista_SE getTipos () {return tipos;}
    public Lista_SE getHabilidades () {return habilidades;}

    // Ler uma string para construir o Pokemon
    public void ler (String entrada) throws Exception
    {
        int quantas_partes = 0;
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

    }

    // construtor
    public Pokemon ()
    {

    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// GERENCIADOR

// classe que gerencia pokemons.
class Gerenciador
{
    // VARS
    private static int quantos = 801;
    private Pokemon pokemons [] = new Pokemon [quantos];

    // todos os nomes
    void imprimir_nomes ()
    {
        int quantos = this.quantos;

        for (int x = 0; x < quantos; x++)
            System.out.println (pokemons [x].getNome ());
    }

    // todos os tipos
    void imprimir_tipos ()
    {
        int quantos = this.quantos;

        for (int x = 0; x < quantos; x++)
        {
            System.out.println ("\nID " + (x+1));
            pokemons [x].getTipos ().imprimir ();
        }
    }

    // todas habilidades
    void imprimir_habilidades ()
    {
        int quantos = this.quantos;

        for (int x = 0; x < quantos; x++)
        {
            System.out.println ("\nID " + (x+1));
            pokemons [x].getHabilidades ().imprimir ();
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
// MAIN

public class Main
{
    public static void main (String args []) throws Exception
    {
        Gerenciador pokemons = new Gerenciador ();

        pokemons.imprimir_habilidades ();
    }
}