/**
 * Enum z modelem stanow Zlecenia określających cykl życia biletu wewnątrz procesu logiki biznesowej.
 */
public enum OrderState {
    NOT_STARTED,
    STARTED,
    DELAYED,
    COMPLETED
}
