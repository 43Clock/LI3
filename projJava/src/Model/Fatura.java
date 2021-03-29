package Model;

import java.io.Serializable;
import java.util.*;

/**
 * Classe que contém todos os dados que compõem e formam uma Fatura e também funções de acesso e obtenção dos seus dados.
 */
public class Fatura implements IFatura, Serializable {
    private String produto;
    private boolean comprado;
    private double[][] fatTotal;
    private int[] quantidadeFilial;
    private Set<String> clientes;

    /**
     * Construtor que recebe um produto para a criação de uma nova Fatura.
     * @param produto produto para o qual será criada uma nova Fatura.
     */
    public Fatura(String produto){
        this.produto = produto;
        this.comprado = false;
        this.fatTotal = new double[3][12];
        this.quantidadeFilial = new int[3];
        this.clientes = new HashSet<>();
    }

    /**
     * Construtor que recebe uma IFatura e insere os seus dados na nova Fatura.
     * @param o IFatura que irá ser copiada para a nova Fatura.
     */
    public Fatura(IFatura o){
        this.produto = o.getProduto();
        this.comprado = o.isComprado();
        this.fatTotal = o.getFatTotal();
        this.quantidadeFilial = o.getQuantidadeFilial();
        this.clientes = o.getClientes();
    }

    /**
     * Função de clone de uma Fatura
     * @return retorna um apontador para a Fatura atual
     */
    public IFatura clone(){
        return new Fatura(this);
    }

    /**
     * Função que recebe uma Venda e altera e atualiza os dados da fatura.
     * @param v Venda recebida com os dados para darmos update à Fatura.
     * @return retorna a IFatura após a mesma ser atualizada.
     */
    public IFatura update(IVenda v){
        this.comprado = true;
        this.fatTotal[v.getFilial()-1][v.getMes()-1] += v.totalSale();
        this.quantidadeFilial[v.getFilial()-1]+=v.getQuantidade();
        this.clientes.add(v.getCliente());
        return this;
    }

    /**
     * Função que nos permite atualizar o produto da Fatura atual.
     * @param produto produto para o qual a Fatura será atualizada.
     */
    public void setProduto(String produto) {
        this.produto = produto;
    }

    /**
     * Função que nos permite obter a faturação total de um produto por mês e filial.
     * @return retorna a faturação total por mês e filial do produto da Fatura atual.
     */
    public double[][] getFatTotal() {
        return fatTotal;
    }

    /**
     * Função que nos permite obter a quantidade de vezes que um produto foi comprado, por filial.
     * @return retorna a quantidade de vezes que o produto da Fatura atual foi comprado, por filial.
     */
    public int[] getQuantidadeFilial() {
        return quantidadeFilial;
    }

    /**
     * Função que nos permite obter os clientes que compraram o produto da Fatura atual.
     * @return retorna o conjunto dos clientes que compraram o produto.
     */
    public Set<String> getClientes() {
        return clientes;
    }

    /**
     * Função que nos permite obter a faturação total de todos os meses e filiais.
     * @return retorna o total faturado em todos os meses e filiais.
     */
    public double getTotal(){
        double r = 0;
            for (int j = 0; j <3 ; j++)
                for (int k = 0; k < 12 ; k++)
                    r += this.fatTotal[j][k];
        return r;
    }

    /**
     * Funçãp que nos permite obter a faturação total para uma dada filial, por mês.
     * @param filial filial para a qual queremos obter a faturação total.
     * @return retorna um Map cuja Key é o mês e cujo Value é o total faturado pela filial nesse mês.
     */
    public Map<Integer,Double> getTotalFilial(int filial){
        Map<Integer,Double> a = new HashMap<>();
        for (int i = 0; i < 12; i++) {
            a.put(i,this.fatTotal[filial-1][i]);
        }
        return a;
    }

    /**
     * Função que nos permite obter o total faturado por mês para todas as filiais.
     * @return retorna um Map cuja Key é o mês e cujo Value é o total faturado do mês.
     */
    public Map<Integer,Double> getTotalMensal(){
        Map<Integer,Double> a = new HashMap<>();
        for (int i = 0; i < 12; i++) {
            int finalI = i;
            a.put(i,Arrays.stream(this.fatTotal).mapToDouble(e->e[finalI]).sum());
        }
        return a;
    }

    /**
     * Função que nos permite obter o produto da Fatura atual.
     * @return retorna o produto da fatura atual.
     */
    public String getProduto() {
        return produto;
    }

    /**
     * Função que nos dá a informação se o produto foi comprado ou não.
     * @return retorna True caso tenha sido comprado e False caso contrário.
     */
    public boolean isComprado() {
        return comprado;
    }

    /**
     * Função que nos permite obter a quantidade de vezes que o produto da Fatura atual foi comprado.
     * @return retorna a quantidade de vezes que o produto foi comprado.
     */
    public int getQuantidade(){
        return Arrays.stream(this.quantidadeFilial).reduce(0, Integer::sum);
    }

    /**
     * Função que nos permite obter o número de Clientes distintos que compraram o produto da Fatura atual.
     * @return retorna o número de Clientes distintos que compraram o produto.
     */
    public int getQuantidadeClientes() {
        return this.clientes.size();
    }
}
