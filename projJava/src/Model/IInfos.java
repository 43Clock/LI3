package Model;

public interface IInfos {

    /**
     *@return Retorna uma String correspondente à path para o ficheiro que contém os clientes.
     */
    String getClientes();

    /**
     *@return Retorna uma String correspondente à path para o ficheiro que contém os produtos.
     */
    String getProdutos();

    /**
     *@return Retorna uma String correspondente à path para o ficheiro que contém as vendas.
     */
    String getVendas();

    /**
     * Função que define a path para o ficheiro que contém os clientes.
     * @param clientes String com a path para o ficheiro que contém os clientes.
     */
    void setClientes(String clientes);

    /**
     * Função que define a path para o ficheiro que contém os produtos.
     * @param produtos String com a path para o ficheiro que contém os produtos.
     */
    void setProdutos(String produtos);

    /**
     * Função que define a path para o ficheiro que contém as vendas.
     * @param vendas String com a path para o ficheiro que contém as vendas.
     */
    void setVendas(String vendas);
}
