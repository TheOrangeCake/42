package transcendence.api42_service.entities;

import jakarta.persistence.*;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Getter
@Setter
@NoArgsConstructor
@Entity
@Table(name="POOL_RESULT")
public class PoolResult {
    @Id
    @GeneratedValue
    private Long id;

    @Column(name="c02")
    private Integer c02Score;

    @Column(name="c03")
    private Integer c03Score;

    @Column(name="c04")
    private Integer c04Score;

    @Column(name="c05")
    private Integer c05Score;

    @Column(name="c06")
    private Integer c06Score;

    @Column(name="c07")
    private Integer c07Score;

    @Column(name="c08")
    private Integer c08Score;

    @Column(name="c09")
    private Integer c09Score;

    @Column(name="c10")
    private Integer c10Score;

    @Column(name="exam_0")
    private Integer exam0Score;

    @Column(name="exam_1")
    private Integer exam1Score;

    @Column(name="exam_2")
    private Integer exam2Score;

    @Column(name="exam_3")
    private Integer exam3Score;

    @OneToOne(mappedBy = "poolResult")
    private User user;
}