package Model;

import java.io.IOException;
import java.io.Serializable;

/**
 * Classe que contém o código de um cliente.
 */
public class Cliente implements ICliente, Serializable {
    private String id;

    /**
     * Construtor da Classe Cliente.
     * @param id String com o código de um cliente.
     */
    public Cliente(String id){
        this.id = id;
    }

    /**
     *@return Retorna uma String correspondente ao código do cliente.
     */
    public String getId() {
        return id;
    }

    /**
     * Função que testa se um cliente é válido ou não.
     * @return Retorna True caso o cliente seja válido e False caso não seja.
     */
    public boolean isValido(){
        return this.id.matches("[A-Z]([1-4]\\d{3}|50{3})");
    }

    /**
     * Função que clona um cliente.
     * @return Retorna o clone do cliente.
     */
    public ICliente clone(){
        return new Cliente(this.getId());
    }

}
