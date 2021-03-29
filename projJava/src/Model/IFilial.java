package Model;

import java.util.*;
import java.util.stream.Collectors;

public interface IFilial {

    /**
     * Função que dada uma Venda nos permite atualizar a informação.
     * @param v Venda recebida com os dados para darmos update à Filial.
     * @return retorna a Filial após a atualização.
     */
    Filial update(IVenda v);

    /**
     * Função que nos permite obter a lista dos clientes melhores compradores.
     * @return retorna a lista dos clientes melhores compradores.
     */
    List<String> melhoresCompradores();

    /**
     * Função que nos permite obter os produtos comprados por um dado cliente e a quantidade.
     * @param cliente Cliente para o qual queremos obter os seus produtos comprados.
     * @return retorna uma Map cuja Key é o produto e cujo Value é o total de vezes que foi comprado pelo cliente.
     */
    Map<String,Integer> produtosCompradosCliente(String cliente);

    /**
     * Função que nos permite obter o número distinto de clientes que compraram um dado produto.
     * @param prod produto para o qual pretendemos saber o número distinto de clientes que o compraram.
     * @return retorna o numero distinto de clientes que compraram o produto.
     */
    int getClienteDiferente(String prod);

    /**
     * Função que nos permite obter o total faturado por um dado Produto num dado mês.
     * @param prod Produto para o qual pretendemos saber a faturacao.
     * @param mes Mes para o qual pretendemos saber a faturacao do produto.
     * @return retorna o total faturado por o produto no mês dado.
     */
    double getFaturacao(String prod,int mes);
}
