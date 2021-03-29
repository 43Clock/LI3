import Model.*;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class Performance {
    public static void main(String[] args) {
        Crono c = new Crono();

        ICatCli clientes = null;
        ICatProd produtos = null;
        try {
            clientes = new CatCli("DadosIniciais/Clientes.txt");
            produtos = new CatProd("DadosIniciais/Produtos.txt");
        } catch (IOException e) {
            System.out.println("Ficheiro de Clientes Invalido");
        }
        ICatCli finalClientes = clientes;
        ICatProd finalProdutos = produtos;

        System.out.println("\n1M Vendas com Files");
        c.start();
        List<String> vendasStringF11 = lerComFiles("DadosIniciais/Vendas_1M.txt");
        c.stop();
        vendasStringF11 = null;
        System.out.println("Ficheiro de 1M lido em "+ c.getTime()+ " segundos");
        c.start();
        List<String> vendasStringF12 = lerComFiles("DadosIniciais/Vendas_1M.txt");
        List<Venda> vendasF12 = vendasStringF12.stream().map(Venda::new).collect(Collectors.toList());
        c.stop();
        vendasStringF12 = null;
        vendasF12 = null;
        System.out.println("Ficheiro de 1M lido e parsed em "+ c.getTime()+ " segundos");
        c.start();
        List<String> vendasStringF13 = lerComFiles("DadosIniciais/Vendas_1M.txt");
        List<Venda> vendasF13 = vendasStringF13.stream().map(Venda::new).filter(v->v.isValido(finalClientes, finalProdutos)).collect(Collectors.toList());
        c.stop();
        vendasStringF13 = null;
        vendasF13 = null;
        System.out.println("Ficheiro de 1M lido, parsed e validado em "+ c.getTime()+ " segundos");


        System.out.println("\n3M Vendas com Files");
        c.start();
        List<String> vendasStringF31 = lerComFiles("DadosIniciais/Vendas_3M.txt");
        c.stop();
        vendasStringF31 = null;
        System.out.println("Ficheiro de 3M lido em "+ c.getTime()+ " segundos");
        c.start();
        List<String> vendasStringF32 = lerComFiles("DadosIniciais/Vendas_3M.txt");
        List<Venda> vendasF32 = vendasStringF32.stream().map(Venda::new).collect(Collectors.toList());
        c.stop();
        vendasStringF32 = null;
        vendasF32 = null;
        System.out.println("Ficheiro de 3M lido e parsed em "+ c.getTime()+ " segundos");
        c.start();
        List<String> vendasStringF33 = lerComFiles("DadosIniciais/Vendas_3M.txt");
        List<Venda> vendasF33 = vendasStringF33.stream().map(Venda::new).filter(v->v.isValido(finalClientes, finalProdutos)).collect(Collectors.toList());
        c.stop();
        vendasStringF33 = null;
        vendasF33 = null;
        System.out.println("Ficheiro de 3M lido, parsed e validado em "+ c.getTime()+ " segundos");


        System.out.println("\n5M Vendas com Files");
        c.start();
        List<String> vendasStringF51 = lerComFiles("DadosIniciais/Vendas_5M.txt");
        c.stop();
        vendasStringF51 = null;
        System.out.println("Ficheiro de 5M lido em "+ c.getTime()+ " segundos");
        c.start();
        List<String> vendasStringF52 = lerComFiles("DadosIniciais/Vendas_5M.txt");
        List<Venda> vendasF52 = vendasStringF52.stream().map(Venda::new).collect(Collectors.toList());
        c.stop();
        vendasStringF52 = null;
        vendasF52 = null;
        System.out.println("Ficheiro de 5M lido e parsed em "+ c.getTime()+ " segundos");
        c.start();
        List<String> vendasStringF53 = lerComFiles("DadosIniciais/Vendas_5M.txt");
        List<Venda> vendasF53 = vendasStringF53.stream().map(Venda::new).filter(v->v.isValido(finalClientes, finalProdutos)).collect(Collectors.toList());
        c.stop();
        vendasStringF53 = null;
        vendasF53 = null;
        System.out.println("Ficheiro de 5M lido, parsed e validado em "+ c.getTime()+ " segundos");



        System.out.println("\n1M Vendas com BR");
        c.start();
        List<String> vendasStringB11 = lerComBufferReader("DadosIniciais/Vendas_1M.txt");
        c.stop();
        vendasStringB11 = null;
        System.out.println("Ficheiro de 1M lido em "+ c.getTime()+ " segundos");
        c.start();
        List<String> vendasStringB12 = lerComBufferReader("DadosIniciais/Vendas_1M.txt");
        List<Venda> vendasB12 = vendasStringB12.stream().map(Venda::new).collect(Collectors.toList());
        c.stop();
        vendasStringB12 = null;
        vendasB12 = null;
        System.out.println("Ficheiro de 1M lido e parsed em "+ c.getTime()+ " segundos");
        c.start();
        List<String> vendasStringB13 = lerComBufferReader("DadosIniciais/Vendas_1M.txt");
        List<Venda> vendasB13 = vendasStringB13.stream().map(Venda::new).filter(v->v.isValido(finalClientes, finalProdutos)).collect(Collectors.toList());
        c.stop();
        vendasStringB13 = null;
        vendasB13 = null;
        System.out.println("Ficheiro de 1M lido, parsed e validado em "+ c.getTime()+ " segundos");


        System.out.println("\n3M Vendas com BR");
        c.start();
        List<String> vendasStringB31 = lerComBufferReader("DadosIniciais/Vendas_3M.txt");
        c.stop();
        vendasStringB31 = null;
        System.out.println("Ficheiro de 3M lido em "+ c.getTime()+ " segundos");
        c.start();
        List<String> vendasStringB32 = lerComBufferReader("DadosIniciais/Vendas_3M.txt");
        List<Venda> vendasB32 = vendasStringB32.stream().map(Venda::new).collect(Collectors.toList());
        c.stop();
        vendasStringB32 = null;
        vendasB32 = null;
        System.out.println("Ficheiro de 3M lido e parsed em "+ c.getTime()+ " segundos");
        c.start();
        List<String> vendasStringB33 = lerComBufferReader("DadosIniciais/Vendas_3M.txt");
        List<Venda> vendasB33 = vendasStringB33.stream().map(Venda::new).filter(v->v.isValido(finalClientes, finalProdutos)).collect(Collectors.toList());
        c.stop();
        vendasStringB33 = null;
        vendasB33 = null;
        System.out.println("Ficheiro de 3M lido, parsed e validado em "+ c.getTime()+ " segundos");


        System.out.println("\n5M Vendas com BR");
        c.start();
        List<String> vendasStringB51 = lerComBufferReader("DadosIniciais/Vendas_5M.txt");
        c.stop();
        vendasStringB51 = null;
        System.out.println("Ficheiro de 5M lido em "+ c.getTime()+ " segundos");
        c.start();
        List<String> vendasStringB52 = lerComBufferReader("DadosIniciais/Vendas_5M.txt");
        List<Venda> vendasB52 = vendasStringB52.stream().map(Venda::new).collect(Collectors.toList());
        c.stop();
        vendasStringB52 = null;
        vendasB52 = null;
        System.out.println("Ficheiro de 5M lido e parsed em "+ c.getTime()+ " segundos");
        c.start();
        List<String> vendasStringB53 = lerComBufferReader("DadosIniciais/Vendas_5M.txt");
        List<Venda> vendasB53 = vendasStringB53.stream().map(Venda::new).filter(v->v.isValido(finalClientes, finalProdutos)).collect(Collectors.toList());
        c.stop();
        vendasStringB53 = null;
        vendasB53 = null;
        System.out.println("Ficheiro de 5M lido, parsed e validado em "+ c.getTime()+ " segundos");

        System.out.println("\n5M Vendas com BR e parallel stream");
        c.start();
        List<String> vendasStringBP53 = lerComBufferReader("DadosIniciais/Vendas_5M.txt");
        List<Venda> vendasBP53 = vendasStringBP53.parallelStream().map(Venda::new).filter(v->v.isValido(finalClientes, finalProdutos)).collect(Collectors.toList());
        c.stop();
        vendasStringB53 = null;
        vendasB53 = null;
        System.out.println("Ficheiro de 5M lido, parsed e validado em "+ c.getTime()+ " segundos");


    }

    private static List<String> lerComFiles(String path){
        List<String> res = new ArrayList<>();
        try {
            res = Files.readAllLines(Paths.get(path), StandardCharsets.UTF_8);
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
        return res;
    }

    private static List<String> lerComBufferReader(String path){
        List<String> res = new ArrayList<>();
        BufferedReader input = null;
        String linha = null;
        try {
            input = new BufferedReader(new FileReader(path));
            while((linha = input.readLine()) != null)
                res.add(linha);
        }
        catch(IOException e) {
            System.out.println(e.getMessage());
        }
        return res;
    }


}
