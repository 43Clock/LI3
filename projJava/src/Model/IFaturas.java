package Model;

import java.util.List;
import java.util.Map;

public interface IFaturas {

    /**
     * Função que nos permite atualizar a informação de uma Fatura.
     * @param v Venda recebida com os dados para darmos update à Fatura.
     * @return retorna Faturas após a Fatura associada ao produto da IVenda, ter sido atualizada.
     */
    Faturas update(IVenda v);

    /**
     * Função que nos permite obter a faturação total de todos protudos presentes em Faturas.
     * @return retorna o total faturado por todos os produtos em conjunto.
     */
    double faturacaoTotal();

    /**
     * Função que nos permite obter o total faturado por mês.
     * @return retorna um Map cuja Key é o mês e cujo Value é o total faturado nesse mês.
     */
    Map<Integer,Double> totalFaturadoMes();

    /**
     * Função que nos permite obter o total faturado por mes para uma dada filial.
     * @param filial filial para o qual pretendemos saber a faturacao mensal.
     * @return retorna um Map cuja Key é o mês e cujo Value é o total faturado pela filial nesse mês.
     */
    Map<Integer,Double> totalFaturadoFilial(int filial);

    /**
     * Função que nos permite obter a lista dos produtos que foram comprados.
     * @return retorna a lista dos produtos que foram comprados.
     */
    List<String> produtosComprados();

    /**
     * Função que nos permite obter a lista dos produtos que nunca foram comprados.
     * @return retorna a lista dos produtos não comprados.
     */
    List<String> produtosNComprados();

    /**
     * Função que nos permite obter a lista de IFatura por ordem decrescente da quantidade de vezes que o produto foi comprado.
     * @return retorna a lista de IFatura por ordem descrescente da quantidade de vezes que o produto associado à IFatura foi comprado.
     */
    List<IFatura> getAllFatOrd();

}
