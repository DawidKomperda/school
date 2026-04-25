import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class UserDeletionTest {
    private Admin admin;
    private Manager manager;
    private Employee employee;

    private Admin adminTarget;
    private Manager managerTarget;
    private Employee employeeTarget;

    @BeforeEach
    public void setUp() {
        admin = new Admin();
        manager = new Manager();
        employee = new Employee();

        adminTarget = new Admin();
        managerTarget = new Manager();
        employeeTarget = new Employee();
    }

    @Test
    public void testEmployeeDeletionPermissions() {
        System.out.println("--- Testing EMPLOYEE attempts to delete users ---");
        assertThrows(SecurityException.class, () -> employee.deleteUser(adminTarget), "Employee should NOT be able to delete Admin");
        assertThrows(SecurityException.class, () -> employee.deleteUser(managerTarget), "Employee should NOT be able to delete Manager");
        assertThrows(SecurityException.class, () -> employee.deleteUser(employeeTarget), "Employee should NOT be able to delete Employee");
    }

    @Test
    public void testManagerDeletionPermissions() {
        System.out.println("--- Testing MANAGER attempts to delete users ---");
        assertThrows(SecurityException.class, () -> manager.deleteUser(adminTarget), "Manager should NOT be able to delete Admin");
        assertTrue(manager.deleteUser(employeeTarget), "Manager should be able to delete Employee");
        assertTrue(manager.deleteUser(managerTarget), "Manager should be able to delete Manager");
    }

    @Test
    public void testAdminDeletionPermissions() {
        System.out.println("--- Testing ADMIN attempts to delete users ---");
        assertTrue(admin.deleteUser(employeeTarget), "Admin should be able to delete Employee");
        assertTrue(admin.deleteUser(managerTarget), "Admin should be able to delete Manager");
        assertTrue(admin.deleteUser(adminTarget), "Admin should be able to delete Admin");
    }
}
