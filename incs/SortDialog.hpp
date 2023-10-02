#ifndef SORT_DIALOG_HPP
#define SORT_DIALOG_HPP

#include <QDialog>
#include <QRadioButton>

enum class sortOption
{
    Default,
    DateDesc,
    DateAsc
};

class SortDialog final : public QDialog
{
    Q_OBJECT

   private:
    QRadioButton* rbDateDesc;
    QRadioButton* rbDateAsc;
    QRadioButton* rbDefault;

   public:
    SortDialog()                                       = delete;
    ~SortDialog()                                      = default;
    SortDialog(const SortDialog& /*other*/)            = delete;
    SortDialog(SortDialog&& /*other*/)                 = delete;
    SortDialog& operator=(const SortDialog& /*other*/) = delete;

    SortDialog(sortOption opt);

    sortOption getSortOption() const;
};

#endif  // SORT_DIALOG_HPP