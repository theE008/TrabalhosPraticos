/**
 * @date: 11/2024
 * @author: Thiago Pereira de Oliveira
 * @details: Meu código fonte dos TPs para Java, onde guardo a base para as futuras atividades
 * do TP 4.
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////
// BIBLIOTECAS

import java.util.Scanner; // não sei fazer scanner do zero ainda
import java.io.File;     // nem criar arquivos do zero

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
    public void ler (String entrada)
    {
        System.out.println (entrada);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// GERENCIADOR

// classe que gerencia pokemons.
class Gerenciador
{
    private static int quantos = 801;
    private Pokemon pokemons [] = new Pokemon [quantos];

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
    }
}