package Model;

import java.util.Map;
import java.util.Set;

public interface IFatura {

    /**
     * Função que recebe uma Venda e altera e atualiza os dados da fatura.
     * @param v Venda recebida com os dados para darmos update à Fatura.
     * @return retorna a IFatura após a mesma ser atualizada.
     */
    IFatura update(IVenda v);

    /**
     * Função que nos permite obter a faturação total de todos os meses e filiais.
     * @return retorna o total faturado em todos os meses e filiais.
     */
    double getTotal();

    /**
     * Funçãp que nos permite obter a faturação total para uma dada filial, por mês.
     * @param filial filial para a qual queremos obter a faturação total.
     * @return retorna um Map cuja Key é o mês e cujo Value é o total faturado pela filial nesse mês.
     */
    Map<Integer,Double> getTotalFilial(int filial);

    /**
     * Função que nos permite obter o total faturado por mês para todas as filiais.
     * @return retorna um Map cuja Key é o mês e cujo Value é o total faturado do mês.
     */
    Map<Integer,Double> getTotalMensal();

    /**
     * Função que nos permite obter o produto da Fatura atual.
     * @return retorna o produto da fatura atual.
     */
    String getProduto();

    /**
     * Função que nos dá a informação se o produto foi comprado ou não.
     * @return retorna True caso tenha sido comprado e False caso contrário.
     */
    boolean isComprado();

    /**
     * Função que nos permite obter a quantidade de vezes que o produto da Fatura atual foi comprado.
     * @return retorna a quantidade de vezes que o produto foi comprado.
     */
    int getQuantidade();

    /**
     * Função que nos permite obter o número de Clientes distintos que compraram o produto da Fatura atual.
     * @return retorna o número de Clientes distintos que compraram o produto.
     */
    int getQuantidadeClientes();

    /**
     * Função que nos permite atualizar o produto da Fatura atual.
     * @param produto produto para o qual a Fatura será atualizada.
     */
    void setProduto(String produto);

    /**
     * Função que nos permite obter a faturação total de um produto por mês e filial.
     * @return retorna a faturação total por mês e filial do produto da Fatura atual.
     */
    double[][] getFatTotal();

    /**
     * Função que nos permite obter a quantidade de vezes que um produto foi comprado, por filial.
     * @return retorna a quantidade de vezes que o produto da Fatura atual foi comprado, por filial.
     */
    int[] getQuantidadeFilial();

    /**
     * Função que nos permite obter os clientes que compraram o produto da Fatura atual.
     * @return retorna o conjunto dos clientes que compraram o produto.
     */
    Set<String> getClientes();

    /**
     * Função de clone de uma Fatura
     * @return retorna um apontador para a Fatura atual
     */
    IFatura clone();
}
