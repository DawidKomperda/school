import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class UserCreationTest {
    private Admin adminUser;
    private Manager manager1;
    private Manager manager2;
    private Employee emp1;
    private Employee emp2;

    @BeforeEach
    public void setUp() {
        adminUser = new Admin();
        manager1 = new Manager();
        manager2 = new Manager();
        emp1 = new Employee();
        emp2 = new Employee();
    }

    @Test
    public void testAdminUserCreationPermissions() {
        assertNotNull(adminUser.createUser(new Admin()), "Admin should be able to create Admin");
        assertNotNull(adminUser.createUser(new Manager()), "Admin should be able to create Manager");
        assertNotNull(adminUser.createUser(new Employee()), "Admin should be able to create Employee");
    }

    @Test
    public void testManagerUserCreationPermissions() {
        assertThrows(SecurityException.class, () -> {
            manager1.createUser(new Admin());
        }, "Manager should NOT be able to create Admin");
        
        assertNotNull(manager1.createUser(new Manager()), "Manager should be able to create Manager");
        assertNotNull(manager2.createUser(new Employee()), "Manager should be able to create Employee");
    }

    @Test
    public void testEmployeeUserCreationPermissions() {
        assertThrows(SecurityException.class, () -> emp1.createUser(new Admin()), "Employee should NOT be able to create Admin");
        assertThrows(SecurityException.class, () -> emp1.createUser(new Manager()), "Employee should NOT be able to create Manager");
        assertThrows(SecurityException.class, () -> emp2.createUser(new Employee()), "Employee should NOT be able to create Employee");
    }

    @Test
    public void testAdminSpecificMethods() {
        adminUser.changePassword(emp1, "new_secure_password");
        assertEquals("new_secure_password", emp1.getPassword(), "Admin should be able to alter employee password.");
    }
}
