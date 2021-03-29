package Model;

import java.io.Serializable;
import java.util.*;
import java.util.stream.Collectors;

/**
 * Classe que contém todos os Produtos associado à sua lista de Vendas, todos os Clientes associados à sua lista de Vendas
 * e também métodos de acesso e utilização de informação.
 */
public class Filial implements IFilial, Serializable {
    private Map<String,List<IVenda>> cliProd;
    private Map<String, List<IVenda>> prodCli;

    /**
     * Construtos por omissão, que inicializa as duas variaveis de instancia.
     */
    public Filial(){
        cliProd = new HashMap<>();
        prodCli = new HashMap<>();
    }

    /**
     * Função que dada uma Venda nos permite atualizar a informação.
     * @param v Venda recebida com os dados para darmos update à Filial.
     * @return retorna a Filial após a atualização.
     */
    public Filial update(IVenda v){
        List<IVenda> cli = cliProd.get(v.getCliente());
        List<IVenda> pro = prodCli.get(v.getProduto());

        if(cli == null){
            cli = new ArrayList<>();
            cli.add(v);
            this.cliProd.put(v.getCliente(),cli);
        }
        else{
            cli.add(v);
        }

        if(pro == null){
            pro = new ArrayList<>();
            pro.add(v);
            this.prodCli.put(v.getProduto(),pro);
        }
        else{
            pro.add(v);
        }
        return this;
    }

    /**
     * Função que nos permite obter a lista dos clientes melhores compradores.
     * @return retorna a lista dos clientes melhores compradores.
     */
    public List<String> melhoresCompradores(){
        return this.cliProd.entrySet().stream().map(a-> new AbstractMap.SimpleEntry<>(a.getKey(),
                                                                                a.getValue().stream().mapToDouble(IVenda::totalSale).sum()))
                                      .sorted(Collections.reverseOrder(Comparator.comparingDouble(Map.Entry::getValue)))
                                      .map(Map.Entry::getKey)
                                      .collect(Collectors.toList());
    }

    /**
     * Função que nos permite obter os produtos comprados por um dado cliente e a quantidade.
     * @param cliente Cliente para o qual queremos obter os seus produtos comprados.
     * @return retorna uma Map cuja Key é o produto e cujo Value é o total de vezes que foi comprado pelo cliente.
     */
    public Map<String,Integer> produtosCompradosCliente(String cliente){
        List<IVenda> aux = this.cliProd.get(cliente);
        if(aux != null)
            return aux.stream().collect(Collectors.toMap(IVenda::getProduto,IVenda::getQuantidade,Integer::sum));
        return null;
    }

    /**
     * Função que nos permite obter o número distinto de clientes que compraram um dado produto.
     * @param prod produto para o qual pretendemos saber o número distinto de clientes que o compraram.
     * @return retorna o numero distinto de clientes que compraram o produto.
     */
    public int getClienteDiferente(String prod){
        List<IVenda> v = this.prodCli.get(prod);
        if(v!=null)
            return (int) v.stream().map(IVenda::getCliente).distinct().count();
        return 0;
    }

    /**
     * Função que nos permite obter o total faturado por um dado Produto num dado mês.
     * @param prod Produto para o qual pretendemos saber a faturacao.
     * @param mes Mes para o qual pretendemos saber a faturacao do produto.
     * @return retorna o total faturado por o produto no mês dado.
     */
    public double getFaturacao(String prod ,int mes){
        return this.prodCli.get(prod).stream().filter(a->a.getMes() == mes).map(IVenda::totalSale).mapToDouble(Double::doubleValue).sum();
    }

}


