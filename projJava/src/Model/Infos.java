package Model;

import java.io.IOException;
import java.io.Serializable;

/**
 * Classe que contem as strings com as paths para os ficheiros onde estão os clientes, os produtos e as vendas.
 */
public class Infos implements IInfos, Serializable {
    private String clientes;
    private String produtos;
    private String vendas;

    /**
     * Construtor da Classe Infos.
     */
    public Infos() {
        this.clientes = "";
        this.produtos = "";;
        this.vendas = "";
    }

    /**
     *@return Retorna umaString correspondente à path para o ficheiro que contém os clientes.
     */
    public String getClientes() {
        return clientes;
    }

    /**
     *@return Retorna uma String correspondente à path para o ficheiro que contém os produtos.
     */
    public String getProdutos() {
        return produtos;
    }

    /**
     *@return Reotrna uma String correspondente à path para o ficheiro que contém as vendas.
     */
    public String getVendas() {
        return vendas;
    }

    /**
     * Função que define a path para o ficheiro que contém os clientes.
     * @param clientes String com a path para o ficheiro que contém os clientes.
     */
    public void setClientes(String clientes) {
        this.clientes = clientes;
    }

    /**
     * Função que define a path para o ficheiro que contém os produtos.
     * @param produtos String com a path para o ficheiro que contém os produtos.
     */
    public void setProdutos(String produtos) {
        this.produtos = produtos;
    }

    /**
     * Função que define a path para o ficheiro que contém as vendas.
     * @param vendas String com a path para o ficheiro que contém as vendas.
     */
    public void setVendas(String vendas) {
        this.vendas = vendas;
    }

}
