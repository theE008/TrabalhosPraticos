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
// POKEMON

// classe pokemon
class Pokemon
{
    // VARS
    private int Id = 0;
    private int geracao = 0;
    private String nome = "";
    private String descricao = "";
    //tipos
    //habilidades
    private double peso = 0.0;
    private double tamanho = 0.0;
    private int razao_de_captura = 0;
    private boolean eh_lendario = false;
    //data

    // GETS
    public int getId () {return Id;}
    public int getGeracao () {return  geracao;}
    public String getNome () {return nome;}

    // Ler uma string para construir o Pokemon
    public void ler (String entrada)
    {
        int quantas_partes = 0;
        String [] corte = entrada.split ("\"");

        // --- parte antes de habilidades (corte [0])
        int quantos_corte_0 = 0;

        String [] corte_0 = corte [0].replaceAll ("^,+|,+$", "").split (",");

        // Id
        this.Id = Integer.parseInt (corte_0 [0]);

        // Geração
        this.geracao = Integer.parseInt (corte_0 [1]);

        // Nome
        this.nome = corte_0 [2];

        // Descrição

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

        pokemons.imprimir_nomes ();
    }
}