package View;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public interface IGestVendasView {
    /**
     * Enum que contem a os menus que podes ser imprimidos.
     */
    enum Menu{
        Inicial,Estaticas,Dinamicas, Mes,Filial,Cliente,Produto,Invalid,OpcaoFilial, NumProd,NumCli,
        Save,SaveDone,Load,LoadDone,Default,LoadT,PathClientes,PathProdutos,PathVendas,PathEstrutura
    }

    /**
     * Metodo que imprime, caso necessário um erro.
     * @param erro O erro a ser imprimido.
     */
    void showErro(String erro);

    /**
     * Método que imprime os resultados da Querie 1 num navegador.
     * @param a A Lista de resultados a imprimir.
     * @param time O tempo que a Querie demorou a ser calculada.
     */
    void showQuerie1(List<String> a,String time);

    /**
     * Método que imprime os resultados da Querie 2.
     * @param a Os Resultados a ser imprimidos.
     * @param mes O mês escolhido pelo utilizador.
     * @param filial A filial escolhida pelo utilizador.
     * @param time O tempo que a Querie demorou a ser calculada.
     */
    void showQuerie2(Map.Entry<Integer,Integer> a, int mes, int filial, String time);

    /**
     * Método que imprime os resultados da Querie 3 numa tabela.
     * @param a Os Resultados a ser imprimidos.
     * @param cliente O cliente que foi usado na Querie.
     * @param time O tempo que a Querie demorou a ser calculada.
     */
    void showQuerie3(List<Map.Entry<Integer,Map.Entry<Integer,Double>>> a, String cliente, String time);

    /**
     * Método que imprime os resultados da Querie 4 numa tabela.
     * @param a Os Resultados a ser imprimidos.
     * @param produto O produto que foi usado na Querie.
     * @param time O tempo que a Querie demorou a ser calculada.
     */
    void showQuerie4(List<Map.Entry<Integer,Map.Entry<Integer,Double>>> a, String produto, String time);

    /**
     * Método que imprime os resultados da Querie 5 numa tabela.
     * @param a Os Resultados a ser imprimidos.
     * @param cliente O cliente que foi usado na Querie.
     * @param time O tempo que a Querie demorou a ser calculada.
     */
    void showQuerie5(List<Map.Entry<String,Integer>> a, String cliente, String time);

    /**
     * Método que imprime os resultados da Querie 6 numa tabela.
     * @param a Os Resultados a ser imprimidos.
     * @param time O tempo que a Querie demorou a ser calculada.
     */
    void showQuerie6(List<Map.Entry<String,Integer>> a, String time);

    /**
     * Método que imprime os resultados da Querie 7 numa tabela.
     * @param a Os Resultados a ser imprimidos.
     * @param time O tempo que a Querie demorou a ser calculada.
     */
    void showQuerie7(Map<Integer,List<String>> a, String time);

    /**
     * Método que imprime os resultados da Querie 8 numa tabela.
     * @param a Os Resultados a ser imprimidos.
     * @param time O tempo que a Querie demorou a ser calculada.
     */
    void showQuerie8(List<Map.Entry<String,Integer>> a, String time);

    /**
     * Método que imprime os resultados da Querie 9 numa tabela.
     * @param a Os Resultados a ser imprimidos.
     * @param produto O produto que foi usado na Querie.
     * @param time O tempo que a Querie demorou a ser calculada.
     */
    void showQuerie9(List<Map.Entry<String,Double>> a, String produto, String time);

    /**
     * Método que imprime os resultados da Querie 10 numa tabela.
     * @param a Os Resultados a ser imprimidos.
     * @param prod O produto que foi usado na Querie.
     * @param time O tempo que a Querie demorou a ser calculada.
     */
    void showQuerie10(Map<Integer,List<Double>> a,String prod, String time);

    /**
     * Método que imprime os resultados da Querie e1.1 numa tabela.
     * @param a Os Resultados a ser imprimidos.
     * @param time O tempo que a Querie demorou a ser calculada.
     */
    void showQEstatica1 (List<String> a, String time);

    /**
     * Método que imprime os resultados da Querie e1.2 numa tabela.
     * @param a Os Resultados a ser imprimidos.
     * @param time O tempo que a Querie demorou a ser calculada.
     */
    void showQEstatica2 (List<List<String>> a, String time);

    /**
     * Método que imprime o tempo que algo demorou a carregar
     * @param time Tempo percorrido.
     */
    void showFirstLoad(String time);

    /**
     * Método que imprime o tempo que algo demorou a carregar
     * @param time Tempo percorrido.
     */
    void showTime(String time);

    /**
     * Método que, dependendo do input, imprime algo.
     * @param m O menu que vai ser imprimido
     */
    void askForPrints(Menu m);
}
