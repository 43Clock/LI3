package Controller;

import Model.IGestVendasModel;
import View.IGestVendasView;

public interface IGestVendasController {
    /**
     * Enum com todos os menus possiveis de apresentar.
     */
    enum Menu{
        Inicial,Estaticas,Dinamicas,Q1,Q2,Q3,Q4,Q5,Q6,Q7,Q8,Q9,Q10,E1,E2,Save,Exit,LoadT,LoadTxt,LoadData
    }

    /**
     * Setter para o model
     * @param m Model a usar
     */
    void setModel(IGestVendasModel m);

    /**
     * Setter para o view
     * @param view View a usar
     */
    void setView(IGestVendasView view);

    /**
     * Método que começa o controller
     */
    void run();
}
