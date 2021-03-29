import Controller.GestVendasController;
import Controller.IGestVendasController;
import Model.GestVendasModel;
import Model.IGestVendasModel;
import View.GestVendasView;
import View.IGestVendasView;

import java.io.IOException;

public class GestVendasAppMVC {

    public static void main(String[] args) throws IOException{
        IGestVendasModel gest = new GestVendasModel("DadosIniciais/Clientes.txt","DadosIniciais/Produtos.txt","DadosIniciais/Vendas_1M.txt");
        IGestVendasController controller = new GestVendasController();
        IGestVendasView view = new GestVendasView();
        controller.setModel(gest);
        controller.setView(view);
        controller.run();

    }
}
