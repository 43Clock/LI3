package Model;

import java.io.Serializable;
import java.util.Map;
import java.util.Objects;

/**
 * Classe que contém todas as informações relativas a uma venda.
 */
public class Venda implements IVenda, Serializable {
    private String cliente;
    private String produto;
    private int mes;
    private int filial;
    private int quantidade;
    private double preco;
    private char tipo;

    /**
     * Construtor da Classe Venda.
     * @param v String com uma venda.
     */
    public Venda(String v){
        String[] aux = v.split(" ");
        if(aux.length != 7) this.preco = -1;
        else{
            this.produto = aux[0];
            this.preco = Double.parseDouble(aux[1]);
            this.quantidade = Integer.parseInt(aux[2]);
            this.tipo = aux[3].toCharArray()[0];
            this.cliente = aux[4];
            this.mes = Integer.parseInt(aux[5]);
            this.filial = Integer.parseInt(aux[6]);
        }
    }

    /**
     * Construtor por cópia da Classe Venda.
     * @param v Venda a copiar.
     */
    public Venda(IVenda v) {
        this.cliente = v.getCliente();
        this.produto = v.getProduto();
        this.mes = v.getMes();
        this.filial = v.getFilial();
        this.quantidade = v.getQuantidade();
        this.preco = v.getPreco();
        this.tipo = v.getTipo();
    }

    /**
     *@return Retorna uma String correspondente ao código do cliente associado á venda.
     */
    public String getCliente() {
        return cliente;
    }

    /**
     *@return Retorna uma String correspondente ao código do produto associado á venda.
     */
    public String getProduto() {
        return produto;
    }

    /**
     *@return Retorna um int correspondente ao mês associado á venda.
     */
    public int getMes() {
        return mes;
    }

    /**
     *@return Retorna um int correspondente à filial associada á venda.
     */
    public int getFilial() {
        return filial;
    }

    /**
     *@return Retorna um int correspondente à quantidade associada á venda.
     */
    public int getQuantidade() {
        return quantidade;
    }

    /**
     *@return Retorna um double correspondente ao preço associado á venda.
     */
    public double getPreco() {
        return preco;
    }

    /**
     *@return Retorna um char correspondente ao tipo associado á venda.
     */
    public char getTipo() {
        return tipo;
    }

    /**
     * Função que calcula o total faturado numa venda.
     *@return Retorna um double correspondente ao total faturado na venda.
     */
    public double totalSale(){
        return this.quantidade*this.preco;
    }

    /**
     * Função que testa se uma venda é válida ou não.
     * @param clientes Map com todos os clientes.
     * @param produtos Map com todos os produtos.
     * @return Retorna True caso a venda seja válido e False caso não seja.
     */
    public boolean isValido(ICatCli clientes, ICatProd produtos){
        return clientes.existe(this.cliente) && produtos.existe(this.produto) &&
               this.filial>= 1 && this.filial <=3 && this.mes >= 1 && this.mes<=12 &&
                (this.tipo == 'P' || this.tipo == 'N') && this.preco >= 0.0 && this.quantidade >=0;
    }

    /**
     * Função que testa se um objeto é igual à venda.
     * @return Retorna True caso o objeto seja igual à venda e False caso não seja.
     */
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Venda venda = (Venda) o;
        return mes == venda.mes &&
                filial == venda.filial &&
                quantidade == venda.quantidade &&
                Double.compare(venda.preco, preco) == 0 &&
                tipo == venda.tipo &&
                Objects.equals(cliente, venda.cliente) &&
                Objects.equals(produto, venda.produto);
    }

    /**
     * Função que define como se escreve uma venda na forma de uma string.
     * @return Retorna a String com a venda escrita.
     */
    public String toString() {
        final StringBuilder sb = new StringBuilder("Venda{");
        sb.append("cliente='").append(cliente).append('\'');
        sb.append(", produto='").append(produto).append('\'');
        sb.append(", mes=").append(mes);
        sb.append(", filial=").append(filial);
        sb.append(", quantidade=").append(quantidade);
        sb.append(", preco=").append(preco);
        sb.append(", tipo=").append(tipo);
        sb.append('}');
        return sb.toString();
    }

    /**
     * Função que clona uma Venda.
     * @return Retorna a Venda clonada.
     */
    public IVenda clone(){
        return new Venda(this);
    }
}
