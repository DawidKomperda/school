/**
 * Klasa pracownika (najniższy szczebel opcji w systemie operacyjnym).
 * Posiada dostęp tylko do podstawowych funkcji ujętych w BaseUser, zazwyczaj 
 * nie ma m.in. prawa do zarzadzania zasobami i użytkownikami.
 */
public class Employee extends BaseUser {

    public Employee() {
        super();
    }

    public Employee(String username, String password) {
        super(username, password);
    }

    @Override
    public String getRoleName() { return "Employee"; }

    @Override
    public boolean canApproveOrders() { return false; }

    @Override
    protected int getSecurityClearance() { return 10; }
}
