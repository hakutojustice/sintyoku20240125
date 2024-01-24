#include "SceneBase.h"
#include "Vec2.h"

class SceneMain;

class SceneStageSelect :
    public SceneBase
{
public:
    SceneStageSelect();
    ~SceneStageSelect() {}

    void Init();
    void Update();
    void Draw();
    void End();

    void SetHandle(int handle) { Graph = handle; }

    // シーンを終了させたいか
    bool IsSceneEnd() const;

    // 次どのステージに行くか
    bool ToStage1() const { return isStage1; }
    bool ToStage2() const { return isStage2; }
    bool ToBackTitke() const { return isBackTitle; }

private:
    enum Select
    {
        kStage1,        // ステージ1
        kStage2,        // ステージ2
        kBackTitle,     // タイトル画面に戻る

        kSclectNum,         // 項目数
    };

    int m_select;    // 選択中のメニュー

private:

    // ステージ1へ行くか、ステージ２へ行くか、タイトル画面に戻るか
    bool isStage1;
    bool isStage2;
    bool isBackTitle;

    // 選択中メニュー四角表示位置
    Vec2 m_selectPos;
};

