package Model;

import Exceptions.InvalidClienteException;
import Exceptions.InvalidFilialException;
import Exceptions.InvalidMesException;
import Exceptions.InvalidProdutoException;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;

public interface IGestVendasModel {

    /**
     * @return Tempo que o model demorou a ser inicializado.
     */
    String getTime();

    /**
     * @return Path correspondente ao ficheiro de vendas.
     */
    String getVendasFile();

    /**
     * @return Path correspondente ao ficheiro de clientes.
     */
    String getClientesFile();

    /**
     * @return Path correspondente ao ficheiro de produtos.
     */
    String getProdutosFile();

    /**
     * Calcula o número de vendas inválidas que estão no ficheiro de vendas.
     * @return Numero de vendas inválidas.
     */
    int numVendasErradas();

    /**
     * Calcula o número total de produtos lidos e validados.
     * @return Numero de produtos válidos que estão no catálogo.
     */
    int numTotalProdutos();

    /**
     * Calcula o número de produtos que foram e que não foram comprados.
     * @return Map Entry em que a key é o número de produtos comprados e value é o número de produtos não comprados.
     */
    Map.Entry<Integer,Integer> getProdutosComprados();

    /**
     * Calcula o número total de clientes lidos e validados.
     * @return Numero de clientes válidos que estão no catálogo.
     */
    int numTotalClientes();

    /**
     * Calcula o número de clientes compradores e não compradores.
     * @return Map Entry em que a key é o número de clientes compradores e value é o número de clientes não compradores.
     */
    Map.Entry<Integer,Integer> getClientesCompradores();

    /**
     * Calcula o número de vendas em que o preço é 0.0.
     * @return Número de vendas a 0.0.
     */
    int getVendasFree();

    /**
     * Calcula a faturação total das vendas.
     * @return Total faturado.
     */
    double getFaturacao();


    //1.2

    /**
     * Calcula o numero de vendas feitas por mês.
     * @return Map em que key corresponde ao mẽs e value corresponde ao número de vendas.
     */
    Map<Integer,Integer> numComprasPorMes();

    /**
     * Método que calcula o total faturado por mês numa certa filial.
     * @param filial Filial para a qual vai ser calculada a faturação.
     * @return Map em que a key é o mẽs e o value é a faturação.
     * @throws InvalidFilialException Exceção para caso a filial seja inválida.
     */
    Map<Integer,Double> faturacaoTotalFilial(int filial) throws InvalidFilialException;

    /**
     * Método que calcula o total de clientes distintos por mês numa certa filial.
     * @param filial Filial para a qual vai ser calculada o número de clientes.
     * @return Map em que a key é o mẽs e o value é a faturação.
     * @throws InvalidFilialException Exceção para caso a filial seja inválida.
     */
    Map<Integer,Integer> clientesPorFilial(int filial) throws InvalidFilialException;


    //querie 1

    /**
     * Calcula a lista ordenada dos produtos que ninguém comprou.
     * @return Lista dos produtos não comprados.
     */
    List<String> produtosNaoComprados();

    //querie 2

    /**
     * Calcula o total de vendas efetuadas e o numero de clientes que fizeram compras num determinado mês.
     * @param mes Mês a calcular.
     * @return Map Entry em que a key é o numero total vendas e value é o numero de clientes distintos.
     * @throws InvalidMesException Exceção para caso o mês seja inválido.
     */
    Map.Entry<Integer,Integer> vendasClientesTotais(int mes) throws InvalidMesException;

    /**
     * Calcula o total de vendas efetuadas e o numero de clientes que fizeram compras num determinado mês e filial.
     * @param mes Mês a calcular.
     * @param filial Filial a calcular.
     * @return Map Entry em que a key é o numero total vendas e value é o numero de clientes distintos.
     * @throws InvalidMesException Exceção para caso o mês seja inválido.
     * @throws InvalidFilialException Exceção para caso a filial seja inválida.
     */
    Map.Entry<Integer,Integer> vendasClientesTotais(int mes,int filial) throws InvalidMesException,InvalidFilialException;

    //querie 3
    /**
     * Calcula o número de compras, o número de produtos distintos e o total gasto por um certo cliente num mês.
     * @param cliente Cliente a procurar.
     * @param mes Mes onde foram feitas as compras
     * @return Map Entry em que a key é o numero de compras, o value é uma map entry onde a key é o numero de produtos distintos e o value é o total gasto.
     * @throws InvalidMesException Exceção para caso o mês seja inválido.
     * @throws InvalidClienteException Exceção para caso o cliente seja inválido.
     */
    Map.Entry<Integer,Map.Entry<Integer,Double>> infoClienteMes(String cliente,int mes) throws InvalidMesException,InvalidClienteException;

    //querie 4

    /**
     alcula o numero de clientes diferentes que compraram um determinado produto, quantas vezes foi comprado e quanto foi faturado num mes
     * @param produto Produto a procurar.
     * @param mes Mes onde foram feitas as compras
     * @return Map Entry em que a key é o numero de clientes diferentes, o value é uma map entry onde a key é o numero de vezes que foi comprado e o value é o total faturado por esse produto.
     * @throws InvalidMesException Exceção para caso o mês seja inválido.
     * @throws InvalidProdutoException Exceção para caso o produto seja inválido.
     */
    Map.Entry<Integer,Map.Entry<Integer,Double>> infoProdutoMes(String produto,int mes) throws InvalidMesException,InvalidProdutoException;

    //querie 5

    /**
     * Determina a lista ordenada de produtos e quantas vezes um dado cliente comprou.
     * @param cliente Cliente a procurar.
     * @return Lista de Map entry em que a key é o produto e o value é a quantidade.
     * @throws InvalidClienteException Exceção para caso o cliente seja inválido.
     */
    List<Map.Entry<String,Integer>> produtosMaisCompradosCliente(String cliente) throws InvalidClienteException;


    //querie 6
    /**
     * Determina a lista ordenada de produtos(por quantidade vendida) e por quantos clientes distintos foi comprado.
     * @param n Numero de produtos a apresentar.
     * @return Lista de Map entry em que a key é o produto e o value é o número de clientes distintos.
     */
    List<Map.Entry<String,Integer>> produtosMaisVendidos(int n);


    //querie 7

    /**
     * Determina o top de clientes por filial.
     * @return Map em que a key é o filial e value é a lista ordenada com os clientes que mais compraram.
     */
    Map<Integer,List<String>> melhoresClientesPorFilial();

    //querie 8

    /**
     * Determina a lista de clientes que compraram mais produtos diferentes
     * @return Lista de Map Entry em que a key é o cliente e o value é o numero de produtos distintos comprados.
     */
    List<Map.Entry<String,Integer>> querie8();

    //querie 9

    /**
     * Determina a lista de clientes que mais compraram um dado produto e quanto gastaram no total.
     * @param produto Produto a procurar.
     * @return Lista de Map Entry ordenada por total gosto em que a key é o cliente e o value é o total gasto.
     * @throws InvalidProdutoException Exceção para caso o produto seja inválido.
     */
    List<Map.Entry<String,Double>> querie9 (String produto) throws InvalidProdutoException;

    //querie 10

    /**
     * Determina a faturacao de um produto por mês e filial.
     * @param prod Produto a procurar.
     * @return Map em que a key é o mês e o value é a lista com as faturacoes para cada filial.
     * @throws InvalidProdutoException Exceção para caso o produto seja inválido.
     */
    Map<Integer,List<Double>> querie10 (String prod) throws InvalidProdutoException;

    /**
     * Guarda o estado atual do Model para um dado ficheiro.
     * @param file Caminho do ficheiro a guardar.
     * @throws IOException Exceção de erro a escrever para o ficheiro.
     */
    void save(String file) throws IOException;
}
