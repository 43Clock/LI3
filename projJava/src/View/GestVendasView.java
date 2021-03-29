package View;

import Model.Cliente;

import java.util.*;
import java.util.stream.Collectors;


/**
 * Classe que contem os metodos que apresentam os resultados das Queries ao utilizador assim como
 * a interface grafica.
 */
public class GestVendasView implements IGestVendasView {

    /**
     * Método que permite a navegação numa lista.
     * @param nav Navegador.
     * @param time O tempo que a Querie demorou a ser calculada.
     * @param title O titulo que fica no topo da pagina.
     */
    private void menuNavegador(INavegador nav,String time,String title){
        Scanner scanner = new Scanner(System.in);
        while (true){
            System.out.println("\t\t--"+ title +"--\t\t\n");
            System.out.println("Querie done in: " + time);
            System.out.println(nav);
            String s = scanner.next();
            switch (s) {
                case "n":
                    nav.next();
                    break;
                case "p":
                    nav.previous();
                    break;
                case "b":
                    return;
                default:
                    try {
                        int i = Integer.parseInt(s);
                        nav.setPage(i);
                    } catch (NumberFormatException e) {
                        System.out.println("Pagina Invalida");
                    }
                    break;
            }
        }
    }

    /**
     * Metodo que imprime, caso necessário um erro.
     * @param erro O erro a ser imprimido.
     */
    public void showErro(String erro){
        if(!erro.equals("")) System.out.println(erro);
    }

    /**
     * Método que imprime os resultados da Querie 1 num navegador.
     * @param a A Lista de resultados a imprimir.
     * @param time O tempo que a Querie demorou a ser calculada.
     */
    public void showQuerie1(List<String> a,String time){
        INavegador nav = new Navegador(a,12,10);
        this.menuNavegador(nav,time,"Produtos não comprados");
    }

    /**
     * Método que imprime os resultados da Querie 2.
     * @param a Os Resultados a ser imprimidos.
     * @param mes O mês escolhido pelo utilizador.
     * @param filial A filial escolhida pelo utilizador.
     * @param time O tempo que a Querie demorou a ser calculada.
     */
    public void showQuerie2(Map.Entry<Integer,Integer> a, int mes, int filial, String time) {
        System.out.println("Querie done in: " + time+"\n");
        if (filial == 0) {
            System.out.println("Vendas no mes " + mes + ": " + a.getKey());
            System.out.println("Número de clientes distintos: " + a.getValue());
        } else {
            System.out.println("Vendas no mes " + mes + " na filial " + filial+" : " + a.getKey());
            System.out.println("Número de clientes distintos: " + a.getValue());
        }
        new Scanner(System.in).nextLine();
    }

    /**
     * Método que imprime os resultados da Querie 3 numa tabela.
     * @param a Os Resultados a ser imprimidos.
     * @param cliente O cliente que foi usado na Querie.
     * @param time O tempo que a Querie demorou a ser calculada.
     */
    public void showQuerie3(List<Map.Entry<Integer,Map.Entry<Integer,Double>>> a, String cliente, String time){
        List<List<String>> res = new ArrayList<>();
        List<String> colunas = new ArrayList<>();
        List<String> linhas = new ArrayList<>();
        linhas.add("Numero de Vendas");
        linhas.add("Produtos Diferentes Comprados");
        linhas.add("Total Gasto");
        List<String> l1 = new ArrayList<>();
        List<String> l2 = new ArrayList<>();
        List<String> l3 = new ArrayList<>();
        System.out.println("\t\t--Informacao do cliente " + cliente +" por mês--\n");
        int i;
        for(i=0;i<12;i++){
            l1.add(a.get(i).getKey().toString());
            l2.add(a.get(i).getValue().getKey().toString());
            l3.add(String.format("%.2f",a.get(i).getValue().getValue()));
        }

        for(i = 0;i<12;i++){
            colunas.add("Mês "+(i+1));
        }
        res.add(l1);
        res.add(l2);
        res.add(l3);
        ITabela tab = new Tabela(linhas,colunas,res);
        System.out.println(tab.toString());
        System.out.println("Querie done in: " + time);
        new Scanner(System.in).nextLine();
    }

    /**
     * Método que imprime os resultados da Querie 4 numa tabela.
     * @param a Os Resultados a ser imprimidos.
     * @param produto O produto que foi usado na Querie.
     * @param time O tempo que a Querie demorou a ser calculada.
     */
    public void showQuerie4(List<Map.Entry<Integer,Map.Entry<Integer,Double>>> a, String produto, String time){
        List<List<String>> res = new ArrayList<>();
        List<String> colunas = new ArrayList<>();
        List<String> linhas = new ArrayList<>();
        System.out.println("Querie done in: " + time+"\n");
        linhas.add("Numero de Vez Comprado");
        linhas.add("Clientes Diferentes que Compraram");
        linhas.add("Total Faturado");
        List<String> l1 = new ArrayList<>();
        List<String> l2 = new ArrayList<>();
        List<String> l3 = new ArrayList<>();
        System.out.println("\t\t--Informacao do produto " + produto +" por mês--\n");
        int i;
        for(i=0;i<12;i++){
            l1.add(a.get(i).getKey().toString());
            l2.add(a.get(i).getValue().getKey().toString());
            l3.add(String.format("%.2f",a.get(i).getValue().getValue()));
        }
        for(i = 0;i<12;i++){
            colunas.add("Mês "+(i+1));
        }
        res.add(l1);
        res.add(l2);
        res.add(l3);

        ITabela tab = new Tabela(linhas,colunas,res);
        System.out.println(tab.toString());
        new Scanner(System.in).nextLine();
    }

    /**
     * Método que imprime os resultados da Querie 5 numa tabela.
     * @param a Os Resultados a ser imprimidos.
     * @param cliente O cliente que foi usado na Querie.
     * @param time O tempo que a Querie demorou a ser calculada.
     */
    public void showQuerie5(List<Map.Entry<String,Integer>> a, String cliente, String time){
        System.out.println("\t\t --Ordem decrescente dos produtos mais comprados pelo cliente " + cliente+"--\t\t\n");
        System.out.println("Querie done in: " + time+"\n");
        List<String> linhas = new ArrayList<>();
        List<String> colunas = new ArrayList<>();
        List<List<String>> res = new ArrayList<>();
        colunas.add("Quantidades");
        for(int i=0; i<a.size(); i++) {
            linhas.add(a.get(i).getKey());
            List<String> aux = new ArrayList<>();
            aux.add(a.get(i).getValue().toString());
            res.add(aux);
        }
        ITabela tab = new Tabela(linhas,colunas,res);
        System.out.println(tab.toString());
        new Scanner(System.in).nextLine();
    }

    /**
     * Método que imprime os resultados da Querie 6 numa tabela.
     * @param a Os Resultados a ser imprimidos.
     * @param time O tempo que a Querie demorou a ser calculada.
     */
    public void showQuerie6(List<Map.Entry<String,Integer>> a, String time){
        System.out.println("\t\t--"+ a.size()+" Produtos mais vendidos em todo o ano--\n");
        System.out.println("Querie done in: " + time+"\n");
        List<String> linhas = new ArrayList<>();
        List<String> colunas = new ArrayList<>();
        List<List<String>> res = new ArrayList<>();
        colunas.add("Quantidades");
        for(int i=0; i<a.size(); i++) {
            linhas.add(a.get(i).getKey());
            List<String> aux = new ArrayList<>();
            aux.add(a.get(i).getValue().toString());
            res.add(aux);
        }

        ITabela tab = new Tabela(linhas,colunas,res);
        System.out.println(tab.toString());
        new Scanner(System.in).nextLine();
    }

    /**
     * Método que imprime os resultados da Querie 7 numa tabela.
     * @param a Os Resultados a ser imprimidos.
     * @param time O tempo que a Querie demorou a ser calculada.
     */
    public void showQuerie7(Map<Integer,List<String>> a, String time){
        System.out.println("\t\t--Top 3 clientes mais gastadores por filial--\n");
        System.out.println("Querie done in: " + time+"\n");
        List<String> linhas = new ArrayList<>();
        List<String> colunas = new ArrayList<>();
        List<List<String>> res = new ArrayList<>();
        colunas.add("Cliente Nº 1");
        colunas.add("Cliente Nº 2");
        colunas.add("Cliente Nº 3");
        linhas.add("Filial 1");
        linhas.add("Filial 2");
        linhas.add("Filial 3");
        for(int i = 0; i<a.size(); i++){
            res.add(a.get(i+1));
        }

        ITabela tab = new Tabela(linhas,colunas,res);
        System.out.println(tab.toString());
        new Scanner(System.in).nextLine();
    }

    /**
     * Método que imprime os resultados da Querie 8 numa tabela.
     * @param a Os Resultados a ser imprimidos.
     * @param time O tempo que a Querie demorou a ser calculada.
     */
    public void showQuerie8(List<Map.Entry<String,Integer>> a, String time) {
        System.out.println("\t\t--Top "+ a.size()+" Clientes que compraram mais produtos diferentes--\n");
        System.out.println("Querie done in: " + time+"\n");
        List<String> linhas = new ArrayList<>();
        List<String> colunas = new ArrayList<>();
        List<List<String>> res = new ArrayList<>();
        colunas.add("Quantidades");
        for(int i = 0; i<a.size(); i++){
            linhas.add(a.get(i).getKey());
            List<String> aux = new ArrayList<>();
            aux.add(a.get(i).getValue().toString());
            res.add(aux);
        }
        ITabela tab = new Tabela(linhas,colunas,res);
        System.out.println(tab.toString());
        new Scanner(System.in).nextLine();
    }

    /**
     * Método que imprime os resultados da Querie 9 numa tabela.
     * @param a Os Resultados a ser imprimidos.
     * @param produto O produto que foi usado na Querie.
     * @param time O tempo que a Querie demorou a ser calculada.
     */
    public void showQuerie9(List<Map.Entry<String,Double>> a, String produto, String time){
        System.out.println("\t\t--Top "+ a.size()+" Clientes que mais compraram os produto " +produto +"--\n");
        System.out.println("Querie done in: " + time+"\n");
        List<String> linhas = new ArrayList<>();
        List<String> colunas = new ArrayList<>();
        List<List<String>> res = new ArrayList<>();
        colunas.add("Total Gasto");
        for(int i = 0; i<a.size(); i++){
            linhas.add(a.get(i).getKey());
            List<String> aux = new ArrayList<>();
            aux.add(String.format("%.2f",a.get(i).getValue()));
            res.add(aux);
        }

        ITabela tab = new Tabela(linhas,colunas,res);
        System.out.println(tab.toString());
        new Scanner(System.in).nextLine();
    }

    /**
     * Método que imprime os resultados da Querie 10 numa tabela.
     * @param a Os Resultados a ser imprimidos.
     * @param prod O produto que foi usado na Querie.
     * @param time O tempo que a Querie demorou a ser calculada.
     */
    public void showQuerie10(Map<Integer,List<Double>> a,String prod, String time){
        System.out.println("\t\t--Informação sobre o produto " + prod +"--\n");
        System.out.println("Querie done in: " + time+"\n");
        List<String> linhas = new ArrayList<>();
        List<String> colunas = new ArrayList<>();
        List<List<String>> res = new ArrayList<>();
        colunas.add("Filial 1");
        colunas.add("Filial 2");
        colunas.add("Filial 3");
        for(int i = 1;i<13;i++){
            linhas.add("Mes "+ i);
        }
        for(int i = 1;i<13;i++){
            List<String> temp = new ArrayList<>();
            for(int j = 0;j<3;j++){
                temp.add(String.format("%.2f",a.get(i).get(j)));
            }
            res.add(temp);
        }

        ITabela tab = new Tabela(linhas,colunas,res);
        System.out.println(tab.toString());
        new Scanner(System.in).nextLine();
    }
    /**
     * Método que imprime os resultados da Querie e1.1 numa tabela.
     * @param a Os Resultados a ser imprimidos.
     * @param time O tempo que a Querie demorou a ser calculada.
     */
    public void showQEstatica1 (List<String> a, String time) {
        List<List<String>> res = new ArrayList<>();
        for(String s:a){
            List<String> aux = new ArrayList<>();
            aux.add(s);
            res.add(aux);
        }
        List<String> colunas = new ArrayList<>();
        colunas.add("Informações");
        List<String> linhas = new ArrayList<>();
        linhas.add("Ficheiro Vendas");
        linhas.add("Ficheiro Clientes");
        linhas.add("Ficheiro Produtos");
        linhas.add("Vendas Invalidas");
        linhas.add("Vendas Gratis");
        linhas.add("Faturação total");
        linhas.add("Total de produtos");
        linhas.add("Produtos Comprados");
        linhas.add("Produtos não Comprados");
        linhas.add("Clientes Compradores");
        linhas.add("Clientes não Compradores");
        System.out.println("Querie done in: " + time+"\n");
        ITabela tab = new Tabela(linhas,colunas,res);
        System.out.println(tab.toString());
        new Scanner(System.in).nextLine();
    }

    /**
     * Método que imprime os resultados da Querie e1.2 numa tabela.
     * @param a Os Resultados a ser imprimidos.
     * @param time O tempo que a Querie demorou a ser calculada.
     */
    public void showQEstatica2 (List<List<String>> a, String time) {
        List<String> colunas = new ArrayList<>();
        List<String> linhas = new ArrayList<>();
        int f = 4;
        for (int i = 1;i<13;i++)
            colunas.add("Mês "+i);
        linhas.add("Total Vendas");
        for (int i = 1;i<f;i++)
            linhas.add("Faturação Filial "+ i);
        for (int i = 1;i<f;i++)
            linhas.add("Clientes Filial "+ i);
        System.out.println("Querie done in: " + time+"\n");
        ITabela tab = new Tabela(linhas,colunas,a);
        System.out.println(tab.toString());
        new Scanner(System.in).nextLine();
    }

    /**
     * Método que imprime o tempo que algo demorou a carregar
     * @param time Tempo percorrido.
     */
    public void showFirstLoad(String time){
        System.out.println("\n\nLoaded in " + time+" seconds");
    }

    /**
     * Método que imprime o tempo que algo demorou a carregar
     * @param time Tempo percorrido.
     */
    public void showTime(String time){
        System.out.println("Done in "+time+" seconds.\n");
    }

    /**
     * Método que, dependendo do input, imprime algo.
     * @param m O menu que vai ser imprimido
     */
    public void askForPrints(Menu m){
        switch (m){
            case Invalid:
                System.out.println("Opção inválida!\n");
                break;
            case Mes:
                System.out.println("Insira o mês a procurar:");
                break;
            case Filial:
                System.out.println("Insira o filial a procurar:");
                break;
            case OpcaoFilial:
                System.out.println("\n0 - Todas as filiais");
                System.out.println("1- Filial 1");
                System.out.println("2- Filial 2");
                System.out.println("3- Filial 3\n");
                break;
            case Cliente:
                System.out.println("Insira o Cliente a procurar:");
                break;
            case Produto:
                System.out.println("Insira o Produto a procurar:");
                break;
            case NumProd:
                System.out.println("Insira o número de Produtos a apresentar:");
                break;
            case NumCli:
                System.out.println("Insira o número de Clientes a apresentar:");
                break;
            case Dinamicas:
                System.out.println("Escolha uma Querie: ");
                System.out.println("1  - Lista dos Produtos não comprados.");
                System.out.println("2  - Numero de vendas e cliente distintos por mes/filial.");
                System.out.println("3  - Numero de compras e produtos distintos que um cliente comprou");
                System.out.println("4  - Numero de vez que um produto foi comprados e por quantos clientes distintos.");
                System.out.println("5  - Lista dos produtos mais comprados por um cliente.");
                System.out.println("6  - Produtos mais vendidos em todo o ano.");
                System.out.println("7  - Top 3 melhores clientes por filial.");
                System.out.println("8  - Cliente que mais compraram produtos distintos.");
                System.out.println("9  - Cliente que mais compraram um certo produto.");
                System.out.println("10 - Faturação total de um certo produto por mês e filial.");
                System.out.println("11 - Regressar ao menu inicial.\n");
                break;
            case Inicial:
                System.out.println("Escolha uma opção:\n");
                System.out.println("1 - Queries Estatisticas.");
                System.out.println("2 - Queries Dinâmicas.");
                System.out.println("3 - Guardar estrutura num ficheiro.");
                System.out.println("4 - Carregar dados.");
                System.out.println("5 - Sair do programa.\n");
                break;
            case Estaticas:
                System.out.println("Escolha uma Querie: ");
                System.out.println("1 - E1.1");
                System.out.println("2 - E1.2");
                System.out.println("3 - Regressar ao menu inicial\n");
                break;
            case Save:
                System.out.println("Caminho e nome do ficheiro para guardar");
                break;
            case SaveDone:
                System.out.println("Save done !!!");
                break;
            case Load:
                System.out.println("Caminho e nome do ficheiro para ler");
                break;
            case LoadDone:
                System.out.println("Load done !!!");
                break;
            case Default:
                System.out.println("Ficheiros Default Carregados (Vendas_1M)\n\n");
                break;
            case LoadT:
                System.out.println("Escolha uma opção:");
                System.out.println("1 - Load novos ficheiros de dados.");
                System.out.println("2 - Load ficheiro de estrutura ");
                System.out.println("3 - Regressar ao menu inicial");
                break;
            case PathClientes:
                System.out.println("Escolha o path para o ficheiro dos Clientes:");
                break;
            case PathProdutos:
                System.out.println("Escolha o path para o ficheiro dos Produtos:");
                break;
            case PathVendas:
                System.out.println("Escolha o path para o ficheiro das Vendas:");
                break;
            case PathEstrutura:
                System.out.println("Escolha o path para o ficheiro da estrutura:");
                break;
        }
    }
}
