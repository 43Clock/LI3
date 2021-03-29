package Model;

import java.io.Serializable;
import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;

/**
 * Classe que contém todos os Produtos associados à sua respetiva Fatura, e métodos de acesso à informação presente nas Faturas.
 */
public class Faturas implements IFaturas, Serializable {
    public Map<String,IFatura> faturas;

    /**
     * Construtor que recebe ICatProd para podermos aceder á lista de todos os produtos e criar uma nova Faturas,
     * com cada produto associado a uma nova Fatura inicialmente vazia.
     * @param c recebe o objeto ICatProd que contém a lista de todos os produtos.
     */
    public Faturas(ICatProd c){
        List<Produto> produtos = c.prodList();
        this.faturas = produtos.stream()
                               .map(Produto::getId)
                               .collect(Collectors.toMap(Function.identity(),Fatura::new));
    }

    /**
     * Função que nos permite atualizar a informação de uma Fatura.
     * @param v Venda recebida com os dados para darmos update à Fatura.
     * @return retorna Faturas após a Fatura associada ao produto da IVenda, ter sido atualizada.
     */
    public Faturas update(IVenda v){
        this.faturas.get(v.getProduto()).update(v);
        return this;
    }

    /**
     * Função que nos permite obter a faturação total de todos protudos presentes em Faturas.
     * @return retorna o total faturado por todos os produtos em conjunto.
     */
    public double faturacaoTotal(){
        return this.faturas.values().stream()
                                    .mapToDouble(IFatura::getTotal)
                                    .sum();
    }

    /**
     * Função que nos permite obter o total faturado por mês.
     * @return retorna um Map cuja Key é o mês e cujo Value é o total faturado nesse mês.
     */
    public Map<Integer,Double> totalFaturadoMes(){
        return this.faturas.values().stream()
                .flatMap(e -> e.getTotalMensal().entrySet().stream())
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue, Double::sum));
    }

    /**
     * Função que nos permite obter o total faturado por mes para uma dada filial.
     * @param filial filial para o qual pretendemos saber a faturacao mensal.
     * @return retorna um Map cuja Key é o mês e cujo Value é o total faturado pela filial nesse mês.
     */
    public Map<Integer,Double> totalFaturadoFilial(int filial){
        return this.faturas.values().stream()
                .flatMap(e -> e.getTotalFilial(filial).entrySet().stream())
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue, Double::sum));

    }

    /**
     * Função que nos permite obter a lista dos produtos que foram comprados.
     * @return retorna a lista dos produtos que foram comprados.
     */
    public List<String> produtosComprados(){
        return this.faturas.values().stream()
                .filter(IFatura::isComprado)
                .map(IFatura::getProduto).sorted()
                .collect(Collectors.toList());
    }

    /**
     * Função que nos permite obter a lista dos produtos que nunca foram comprados.
     * @return retorna a lista dos produtos não comprados.
     */
    public List<String> produtosNComprados(){
        return this.faturas.values().stream()
                .filter(a->!a.isComprado())
                .map(IFatura::getProduto)
                .sorted()
                .collect(Collectors.toList());
    }

    /**
     * Função que nos permite obter a lista de IFatura por ordem decrescente da quantidade de vezes que o produto foi comprado.
     * @return retorna a lista de IFatura por ordem descrescente da quantidade de vezes que o produto associado à IFatura foi comprado.
     */
    public List<IFatura> getAllFatOrd(){
        return this.faturas.values().parallelStream()
                                    .filter(IFatura::isComprado)
                                    .sorted((a,b)->{
                                        if(a.getQuantidade() == b.getQuantidade())
                                            return a.getProduto().compareTo(b.getProduto());
                                        return b.getQuantidade()-a.getQuantidade();
                                    })
                                    .collect(Collectors.toList());
    }
}
