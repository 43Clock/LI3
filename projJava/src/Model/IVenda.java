package Model;

public interface IVenda {

    /**
     *@return Retorna uma String correspondente ao código do cliente associado á venda.
     */
    String getCliente();

    /**
     *@return Retorna uma String correspondente ao código do produto associado á venda.
     */
    String getProduto();

    /**
     *@return Retorna um int correspondente ao mês associado á venda.
     */
    int getMes();

    /**
     *@return Retorna um int correspondente à filial associada á venda.
     */
    int getFilial();

    /**
     *@return Retorna um int correspondente à quantidade associada á venda.
     */
    int getQuantidade();

    /**
     *@return Retorna um double correspondente ao preço associado á venda.
     */
    double getPreco();

    /**
     *@return Retorna um char correspondente ao tipo associado á venda.
     */
    char getTipo();

    /**
     * Função que calcula o total faturado numa venda.
     *@return Retorna um double correspondente ao total faturado na venda.
     */
    double totalSale();

    /**
     * Função que testa se uma venda é válida ou não.
     * @param clientes Map com todos os clientes.
     * @param produtos Map com todos os produtos.
     * @return Retorna True caso a venda seja válido e False caso não seja.
     */
    boolean isValido(ICatCli clientes, ICatProd produtos);

    /**
     * Função que testa se um objeto é igual à venda.
     * @return Retorna True caso o objeto seja igual à venda e False caso não seja.
     */
    boolean equals(Object o);

    /**
     * Função que define como se escreve uma venda na forma de uma string.
     * @return Retorna a String com a venda escrita.
     */
    String toString();

    /**
     * Função que clona uma Venda.
     * @return Retorna a Venda clonada.
     */
    IVenda clone();
}
